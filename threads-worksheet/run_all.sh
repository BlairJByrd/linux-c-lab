#!/usr/bin/env bash
for p in bin/*; do
    echo "===== $p ====="
    "$p"
    echo
done
