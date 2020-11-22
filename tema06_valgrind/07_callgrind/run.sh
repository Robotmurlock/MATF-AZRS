#!/bin/bash  
# Constants

vcgout="callgrind.out"

# Extracting file name without extension
fullname="$1"
name="${fullname%%.*}"
exename="$name.out"

# Compilation
gcc -g -o "$exename" "$fullname"

# Callgrind
valgrind --tool=callgrind --callgrind-out-file="$vcgout" "./$exename"

# Kcachegrind
kcachegrind "$vcgout"

