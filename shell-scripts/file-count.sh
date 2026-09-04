#!/bin/bash
read -p "Enter directory: " DIR
echo "File counts in $DIR:" >> file-count-log.txt
find "$DIR" -type f | sed 's/.*\.//' | sort | uniq -c >> file-count-log.txt
cat file-count-log.txt
