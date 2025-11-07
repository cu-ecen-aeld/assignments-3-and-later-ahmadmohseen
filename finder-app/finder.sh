#!/bin/sh

# Assign arguments to descriptive variable names
filesdir=$1
searchstr=$2

# Check if both arguments were specified
if [ $# -ne 2 ]; then
    echo "Error: Both a directory path and a search string are required."
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

# Check if filesdir is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: '$filesdir' is not a directory."
    exit 1
fi

# Find the number of files (X)
# -type f ensures we only count regular files (not directories, links, etc.)
# We pipe to wc -l to count the number of lines of output from find
X=$(find "$filesdir" -type f | wc -l)

# Find the number of matching lines (Y)
# We use find to get the list of files, then pass them to grep.
# -I tells grep to ignore binary files.
# We pipe the output of grep to wc -l to count the total matching lines.
Y=$(find "$filesdir" -type f -exec grep -I "$searchstr" {} + 2>/dev/null | wc -l)

# Print the final message
echo "The number of files are $X and the number of matching lines are $Y"
