#!/bin/bash
# Colors for output
red=$(tput setaf 1)
green=$(tput setaf 2)
blue=$(tput setaf 4)
normal=$(tput sgr0)

# Get absolute paths
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"
RESULTS_DIR="$PROJECT_ROOT/benchmark_results"

# Try to find the executable
EXECUTABLE=""
for possible_name in program aids3-program; do
    if [ -f "$BUILD_DIR/$possible_name" ]; then
        EXECUTABLE="$BUILD_DIR/$possible_name"
        break
    fi
done

if [ -z "$EXECUTABLE" ]; then
    echo "${red}Error: Could not find executable in $BUILD_DIR${normal}"
    echo "Please build the project first:"
    echo "  mkdir -p build && cd build && cmake .. && make"
    exit 1
fi

echo "${green}Found executable: $EXECUTABLE${normal}"

# Create results directory
mkdir -p "$RESULTS_DIR"

# Initialize CSV files with headers
echo "graph_type,size,operation,time" > "$RESULTS_DIR/benchmark_time.csv"
echo "graph_type,size,operation,memory" > "$RESULTS_DIR/benchmark_memory.csv"

# Benchmark parameters - większe rozmiary grafów
graph_types=("table" "list" "matrix")
operations=("find" "toposort kahn" "toposort tarjan")
sizes=(100 500 1000 2000 5000)  # Znacznie większe grafy dla lepszego zróżnicowania

# Function to format with 8 decimal precision
format_precision() {
    printf "%.8f" "$1"
}

# Function to get high-resolution time in seconds (floating point)
get_highres_time() {
    python3 -c 'import time; print(time.time())'
}

# Run benchmarks
for size in "${sizes[@]}"; do
    for graph_type in "${graph_types[@]}"; do
        for op in "${operations[@]}"; do
            echo "${blue}Running: $graph_type, size $size, $op${normal}"
            
            # Create input commands file
            input_file=$(mktemp)
            {
                echo "$graph_type"
                echo "$size"
                echo "10"  # Mniejsze nasycenie dla dużych grafów
                
                if [[ "$op" == "find" ]]; then
                    echo "find"
                    echo "0"
                    echo "$((size-1))"
                else
                    echo "$op"
                fi
                echo "quit"
            } > "$input_file"

            # Run the program with precise timing
            output_file=$(mktemp)
            error_file=$(mktemp)
            cd "$PROJECT_ROOT"
            
            # Warm-up run to avoid cold-start bias
            "$EXECUTABLE" --generate < "$input_file" >/dev/null 2>&1
            
            # Actual measurement
            start_time=$(get_highres_time)
            "$EXECUTABLE" --generate < "$input_file" > "$output_file" 2>"$error_file"
            exit_code=$?
            end_time=$(get_highres_time)
            
            # Calculate duration
            duration=$(echo "$end_time - $start_time" | bc -l)
            
            # Get memory usage
            mem=$(/usr/bin/time -f "%M" "$EXECUTABLE" --generate < "$input_file" 2>&1 >/dev/null | head -n1)
            
            # Verify numeric results
            if [[ "$duration" =~ ^[0-9.]+$ ]] && [[ "$mem" =~ ^[0-9]+$ ]]; then
                formatted_time=$(format_precision "$duration")
                echo "$graph_type,$size,$op,$formatted_time" >> "$RESULTS_DIR/benchmark_time.csv"
                echo "$graph_type,$size,$op,$mem" >> "$RESULTS_DIR/benchmark_memory.csv"
                echo "${green}Results: time=${formatted_time}s, memory=${mem}KB${normal}"
            else
                echo "${red}Invalid results: duration='$duration', memory='$mem'${normal}"
                echo "Error output:"
                cat "$error_file"
            fi
            
            # Clean up
            rm "$input_file" "$output_file" "$error_file" 2>/dev/null
            
            # Short pause between tests
            sleep 1
        done
    done
done

echo "${green}Benchmark completed successfully!${normal}"
echo "Results saved to:"
echo "  - $RESULTS_DIR/benchmark_time.csv"
echo "  - $RESULTS_DIR/benchmark_memory.csv"