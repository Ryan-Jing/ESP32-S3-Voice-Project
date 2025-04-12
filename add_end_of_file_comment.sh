#!/bin/bash

# This script will append "// end of file_name.filetype" to each file.
# Loop through each file passed as argument
for file in "$@"; do
  # Get the file name (without path)
  filename=$(basename "$file")
  # Get the file extension
  extension="${filename##*.}"
  # Append the comment
  echo "// end of ${filename}" >> "$file"
done
