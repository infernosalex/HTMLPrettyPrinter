#!/bin/bash

# ASCII Art Header
echo "                                                                                                                        
 _     _  _______   __   __   _        _____                 _    _           _____          _         _                
(_)   (_)(__ _ __) (__)_(__) (_)      (_____)   _      ____ (_)_ (_)_        (_____)   _    (_) _     (_)_   ____  _    
(_)___(_)   (_)   (_) (_) (_)(_)      (_)__(_) (_)__  (____)(___)(___) _   _ (_)__(_) (_)__  _ (_)__  (___) (____)(_)__ 
(_______)   (_)   (_) (_) (_)(_)      (_____)  (____)(_)_(_)(_)  (_)  (_) (_)(_____)  (____)(_)(____) (_)  (_)_(_)(____)
(_)   (_)   (_)   (_)     (_)(_)____  (_)      (_)   (__)__ (_)_ (_)_ (_)_(_)(_)      (_)   (_)(_) (_)(_)_ (__)__ (_)   
(_)   (_)   (_)   (_)     (_)(______) (_)      (_)    (____) (__) (__) (____)(_)      (_)   (_)(_) (_) (__) (____)(_)   
                                                                        __(_)                                           
                                                                       (___)                                             "

# Initialize variables
print_to_console=false
replace_original=false
output_file=""
input_file=""

# Check if input file is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: hpp <input_file> [options]"
    echo "Options:"
    echo "  -p, --print          Print the formatted output to the console"
    echo "  -r, --replace        Replace the original file"
    echo "  -o, --output <FILE>  Write the formatted output to FILE"
    exit 1
fi

input_file="$1"
shift

# Check if the provided file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

# Parse options
while [[ "$#" -gt 0 ]]; do
    key="$1"

    case $key in
        -p|--print)
            print_to_console=true
            shift
            ;;
        -r|--replace)
            replace_original=true
            shift
            ;;
        -o|--output)
            output_file="$2"
            shift 2
            ;;
        *)
            echo "Invalid option: $1"
            echo "Usage: $0 <input_file> [options]"
            echo "Options:"
            echo "  -p, --print        Print the formatted output to the console"
            echo "  -r, --replace      Replace the original file"
            echo "  -o, --output <FILE>  Write the formatted output to FILE"
            exit 1
            ;;
    esac
done

# List of self-closing tags
self_closing_tags="area|base|br|col|embed|hr|img|input|link|meta|param|source|track|wbr"

# Initialize indent level
indent=0
# Initialize output content
output_content=""

while IFS= read -r line || [[ -n "$line" ]]; do
    # Remove whitespace
    line=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    # Skip empty lines
    [ -z "$line" ] && continue

    # If line has closing tag, decrease indent
    if echo "$line" | grep -q "^</"; then
        ((indent--))
    fi

    # Format line with indentation
    line_indented=$(printf "%*s%s\n" $((indent * 4)) "" "$line")

    if [ -z "$output_content" ]; then
        output_content="$line_indented"
    else
        output_content="$output_content"$'\n'"$line_indented"
    fi

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

done < "$input_file"

if [ "$print_to_console" = true ]; then
    echo "$output_content"
fi

if [ "$replace_original" = true ]; then
    echo "$output_content" > "$input_file"
fi

if [ -n "$output_file" ]; then
    echo "$output_content" > "$output_file"
fi

# Default action if no option is provided
if [ "$print_to_console" = false ] && [ "$replace_original" = false ] && [ -z "$output_file" ]; then
    echo "$output_content"
fi