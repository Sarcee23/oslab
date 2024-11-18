#!/bin/bash

########################################################################################################################
# Name : Subhayan Roy Chowdhury
# Roll: 002211001096
# Date: 28/10/2024
# IT UG3 A2
#
# Assignment Details:ASSIGNMENT – 8 (10 Marks) [CO1]
# (Shell Script Programming)
#
#    1. Create a directory ‘All My Cprogs Files’ in your home directory.
#
#    2. Move all the C files to the new creating directory.
#
#   3. Show the list of files in your current directory.
#
#    4. Show Current working directory.
#
#    5. Display date in the dd:mm:yy format
#
#    6. Count the number of files in your home directory
#
#    7. Create a file that lists all of the .C files in your directory.
#
#    8. Write a script for addition of two numbers for real numbers also.
#
#    9. Write a script to convert string lower to upper and upper to lower from a file.
#
#    10. Read ‘n’ and generate a pattern given below.
#1
#1 2
#1 2 3
#1 2 3 4
#
# Compilation command: chmod +x 096_8.sh; //to give necessary permission to the file
#
# Execution command : ./096_8.sh
#
# Sample output:
#
#[be2296@localhost ass8]$ ./ass8.sh
#Creating directory 'AllCprogFiles' ...
#Moving C Files..
#Found .c files in current directory, moving them...
#Error moving files, they may already be there
#Files in current directory:
#abc.txt  add_numbers.sh  ass8.sh  case_converter.sh  c_files_list.txt  converted_abc.txt  pattern.sh  whatsup.c
#Current working directory:
#/home/usr/student/ug/yr22/be2296/OS/ass8
#Current date:
#28/10/24
#Number of files in home directory:
#8
#Creating list of .c files..
#Creating addition Script..
#Creating case converter script..
#Creating pattern generation script..
#All scripts have been created!

##########################################################################################################################


# 1. Create directory
echo "Creating directory 'AllCprogFiles' ..."
mkdir -p "$HOME/AllCprogFiles"

# 2. Move C Files
echo "Moving C Files.."
#First check current directory for .c files
if ls *.c>/dev/null 2>&1; then
        echo "Found .c files in current directory, moving them..."
        mv "$HOME"/*.c "$HOME/AllCprogFiles/" 2>/dev/null || echo "Error moving files, they may already be there"
else
        echo "No .c files found in current directory"
fi


#3. List files in current directory
echo "Files in current directory:"
ls

#4. Show current working directory
echo "Current working directory:"
pwd

#5 . Display date in dd:mm:yy format
echo "Current date:"
date +%d/%m/%y

#6. Count files in home directory
echo "Number of files in home directory:"
find "$HOME" -maxdepth 1 -type f | wc -l

# 7. Create file listing .c files
echo "Creating list of .c files.."
if [ -d "$HOME/AllCprogFiles" ] && ls "$HOME/AllCprogFiles"/*.c >/dev/null 2>&1; then
        ls "$HOME/AllCprogFiles"/*.c > c_files_list.txt
else
        echo "No .c files found in AllCprogFIles directory" >c_files_list.txt
fi

# 8. Addition of two numbers (including real numbers)
echo "Creating addition Script.."
cat > add_numbers.sh <<'EOF'
#!/bin/bash
echo "Enter first number:"
read num1
echo "Enter second number:"
read num2
sum=$(echo "$num1 + $num2" | bc)
echo "Sum is: $sum"
EOF
chmod +x add_numbers.sh


# 9 . Convert string case
echo "Creating case converter script.."
cat > case_converter.sh <<'EOF'
#!/bin/bash

# Ask for input file
echo "Enter filename:"
read -r filename

# Check if file exists
if [ ! -f "$filename" ]; then
    echo "File not found!"  # Fixed: Added space after echo
    exit 1
fi

# Create output filename
output_file="converted_$filename"

# Convert lower to upper and upper to lower
while IFS= read -r line; do    # Fixed: Removed space around =
    converted=""    # Fixed: Removed space around =
    for ((i=0; i<${#line}; i++)); do    # Fixed: Removed space after for
        char="${line:$i:1}"    # Fixed: Removed spaces around =
        if [[ "$char" =~ [A-Z] ]]; then
            converted="$converted${char,,}"    # Fixed: Removed space around =
        elif [[ "$char" =~ [a-z] ]]; then    # Fixed: Fixed syntax error in condition
            converted="$converted${char^^}"    # Fixed: Removed space around =
        else
            converted="$converted$char"
        fi
    done
    echo "$converted"
done < "$filename" > "$output_file"

echo "Converted text saved in $output_file"
EOF
chmod +x case_converter.sh

#10 . Pattern Generation
echo "Creating pattern generation script.."
cat > pattern.sh << 'EOF'
#!/bin/bash
echo "Enter number of rows:"
read n

if ! [[ "$n" =~ ^[0-9]+$ ]]; then
        echo "Error: Invalid input! PLease enter a positive number."
        exit 1
fi

for ((i=1; i<=n; i++))
do
        for ((j=1; j<=i; j++))
        do
                echo -n "$j"
        done
        echo ""
done
EOF
chmod +x pattern.sh

echo "All scripts have been created!"