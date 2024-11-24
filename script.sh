#!/bin/bash

# Initialize indent level
indent=0

while IFS= read -r line; do
    # Remove whitespace
    line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    # If line has closing tag, decrease indent
    if echo "$line" | grep -q "^</"; then
        ((indent--))
    fi

    # Print the line with indentation
    printf "%*s%s\n" $((indent * 4)) "" "$line"

    # If line has opening tag, increase indent
    if echo "$line" | grep -q "^<[^/]"; then
        ((indent++))
    fi

done < "$1"