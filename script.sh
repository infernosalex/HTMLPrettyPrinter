#!/bin/bash

# List of self-closing tags
self_closing_tags="area|base|br|col|embed|hr|img|input|link|meta|param|source|track|wbr"

# Initialize indent level
indent=0

while IFS= read -r line || [[ -n "$line" ]]; do
    # Remove whitespace
    line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    # Skip empty lines
    [ -z "$line" ] && continue

    # If line has closing tag, decrease indent
    if echo "$line" | grep -q "^</"; then
        ((indent--))
    fi

    # Print the line with indentation
    printf "%*s%s\n" $((indent * 4)) "" "$line"

    # If line has opening tag, increase indent
    # Ignore:
    # - self-closing tags
    # - inline tags
    # - special tags (starting with <!)
    if echo "$line" | grep -q "^<[^/!]" && \
       ! echo "$line" | grep -q "/>$" && \
       ! echo "$line" | grep -q "^<.*>.*</.*>" && \
       ! echo "$line" | grep -qE "^<($self_closing_tags)[[:space:]>]"; then
        ((indent++))
    fi

done < "$1"