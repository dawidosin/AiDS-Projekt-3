#!/bin/bash
blue=$(tput setaf 4)
gray=$(tput setaf 7)
green=$(tput setaf 2)
teal=$(tput setaf 6)
normal=$(tput sgr0)

# Path to the executable (in build/)
EXECUTABLE="../build/main"

for representation in "representations/"*; do
    for routine in "routines/"*; do
        for benchmark in "benchmark/generate."*; do
            instance_size=${benchmark##*.}
            
            # Temporary log file for colored output
            tmpLogFile=$(mktemp)
            cat > "$tmpLogFile" <<EOF
$normal============================[INSTANCE SIZE $instance_size]============================$green
Running the $routine benchmark for $representation. 
$normal============================[Input]============================$gray
$(cat "$representation" "$benchmark" "$routine" <(echo "$instance_size") <(echo exit))
$normal============================[Program Output]===================$teal 

EOF
            printf "%s" "$(more "$tmpLogFile")"

            # Temporary file for program output
            tmpFile=$(mktemp)

            # Run the benchmark (from the scripts/ folder)
            run_project="$EXECUTABLE --benchmark"
            result=$(/usr/bin/time -f "%S|%M" "$run_project" < <(cat "$representation" "$benchmark" "$routine" <(echo "$instance_size") <(echo exit)) 2>&1 >"$tmpFile")
            
            # Extract time and memory
            mem=${result##*|}
            time=${result%|*}

            # Save to CSV (in project root)
            echo "$(basename "$representation"),$instance_size,$time" >> "$(basename "$routine")_benchmark_time.csv"
            echo "$(basename "$representation"),$instance_size,$mem" >> "$(basename "$routine")_benchmark_memory.csv"
            
            # Append results to log
            cat > "$tmpLogFile" <<EOF

$(cat "$tmpFile")
$normal============================[usr/bin/time]=====================$green
time = $time seconds | memory used = $mem KBi
Saved to $(basename "$routine")_benchmark_time.csv and $(basename "$routine")_benchmark_memory.csv

$normal
EOF
            printf "%s" "$(more "$tmpLogFile")"
        done
    done
done