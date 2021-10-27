#!/bin/bash  
# Constants

vcgout="callgrind.out"
exename="bench.out"
default_input="sample.txt"

# Parameteres
keyword=$1
input=$2

if [[ "$keyword" == "" ]]
then
    echo "Empty keyword!"
    exit
fi

if [[ "$input" == "" ]]
then
    input="$default_input"
fi

# Compilation
g++ -std=c++17 -g -o "$exename" main.cpp

# Callgrind
valgrind --tool=callgrind --callgrind-out-file="$vcgout" "./$exename" "$input" "$keyword"

# Kcachegrind
kcachegrind "$vcgout"

# cleanup
rm "$vcgout" "$exename"
