#!/bin/bash

# Set color codes for pretty output (optional)
blue=$(tput setaf 4)
gray=$(tput setaf 7)
green=$(tput setaf 2)
teal=$(tput setaf 6)
normal=$(tput sgr0)

# Executable path
run_project="./build/program --generate"

# Define representations (graph types)
representations=("list" "matrix" "table")

# Define benchmarks as (nodes saturation)
benchmarks=(
    "small 200 30"
    "medium 500 50"
    "large 1000 60"
)

# Define routines (action and extra inputs)
declare -A routines
routines[kahn_sort]="toposort kahn"
routines[tarjan_sort]="toposort tarjan"
routines[find]="find"$'\n'"0"$'\n'"1"

# CSV headers (optional)
echo "Representation,Instance,Time" > benchmark_time.csv
echo "Representation,Instance,Memory" > benchmark_memory.csv

# Main loops
for rep in "${representations[@]}"; do
    for bench in "${benchmarks[@]}"; do
        IFS=' ' read -r instance_name nodes saturation <<< "$bench"

        for routine_name in "${!routines[@]}"; do
            tmpLogFile=$(mktemp)
            tmpFile=$(mktemp)

            # Compose the full stdin input
            full_input="$rep"$'\n'"$nodes"$'\n'"$saturation"$'\n'"${routines[$routine_name]}"$'\n'"quit"

            # Initial log
            cat > "$tmpLogFile" <<EOF
$normal============================[INSTANCE SIZE $instance_name]============================$green
Running '$routine_name' on representation '$rep'
$normal============================[Input]============================$gray
$full_input
$normal============================[Program Output]===================$teal
EOF

            printf "%s\n" "$(cat "$tmpLogFile")"

            # Measure time
            start=$(date +%s.%N)
            echo "$full_input" | $run_project > "$tmpFile"
            end=$(date +%s.%N)
            time=$(echo "$end - $start" | bc -l)

            # Measure memory
            mem=$( { /usr/bin/time -f "%M" $run_project <<< "$full_input" > /dev/null; } 2>&1 | tail -n 1 | tr -dc '0-9' )


            # Save to CSV
            echo "$rep,$instance_name,$(printf "%.8f" "$time")" >> benchmark_time.csv
            echo "$rep,$instance_name,$mem" >> benchmark_memory.csv

            # Output log
            cat > "$tmpLogFile" <<EOF

$(cat "$tmpFile")
$normal============================[usr/bin/time]=====================$green
time = $(printf "%.8f" "$time") seconds | memory = ${mem} KB
Saved to benchmark_time.csv and benchmark_memory.csv
$normal
EOF

            printf "%s\n" "$(cat "$tmpLogFile")"

            # Cleanup (optional)
            rm "$tmpFile" "$tmpLogFile"
        done
    done
done