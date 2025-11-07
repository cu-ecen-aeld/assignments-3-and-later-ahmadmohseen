#!/bin/bash

# Check if both arguments are provided
if [ $# -lt 2 ]; then
    echo "Error: Missing arguments"
    echo "Usage: $0 <writefile> <writestr>"
    exit 1
fi

writefile="$1"
writestr="$2"

# Get the directory path from the file path
dirpath=$(dirname "$writefile")

# Create the directory path if it doesn't exist
if ! mkdir -p "$dirpath" 2>/dev/null; then
    echo "Error: Could not create directory path $dirpath"
    exit 1
fi

# Write the content to the file
if ! echo "$writestr" > "$writefile" 2>/dev/null; then
    echo "Error: Could not create file $writefile"
    exit 1
fi

# Success
exit 0

