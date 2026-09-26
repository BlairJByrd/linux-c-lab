#!/usr/bin/env bash
set -e
mkdir -p bin
for f in *.c; do
    gcc -Wall -pthread "$f" -o "bin/${f%.c}"
done
echo "Built:"; ls bin
