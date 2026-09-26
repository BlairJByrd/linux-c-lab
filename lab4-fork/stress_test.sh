#!/usr/bin/env bash
# Q2: launch N clients at once and time it. Usage: ./stress_test.sh [count]
N=${1:-50}
echo "Launching $N simultaneous clients..."
start=$(date +%s.%N)
seq "$N" | xargs -P "$N" -I {} ./client >/dev/null 2>&1
end=$(date +%s.%N)
echo "Done. $N clients finished in $(echo "$end - $start" | bc) seconds."
