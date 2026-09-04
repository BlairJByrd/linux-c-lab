#!/bin/bash
read -p "Enter filename: " FILE
if [ -f "$FILE" ]; then
    echo "File exists. Details:"
    ls -l "$FILE"
else
    echo "File does not exist."
fi
