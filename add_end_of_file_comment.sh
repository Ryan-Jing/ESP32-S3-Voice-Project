#!/bin/bash

# This script will append "// end of file_name.filetype" to each file.

for file in "$@"; do
    filename=$(basename "$file")
    comment="// end of ${filename}"

    # Trim trailing whitespace from the last line
    last_line=$(tail -n 1 "$file" | tr -d '\r\n')

    # Check if the last line is the comment
    if [[ "$last_line" != "$comment" ]]; then
    echo "$comment" >> "$file"
    fi
done
