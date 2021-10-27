#!/bin/bash  
# Constants

vcgout="callgrind.out"
exename="bench.out"
input="sample.txt"

# Parameteres
keyword=$1
if [[ "$keyword" == "" ]]
then
    echo "Empty keyword!"
    exit
fi


# Compilation
g++ -std=c++17 -g -o "$exename" main.cpp

# Callgrind
valgrind --tool=callgrind --callgrind-out-file="$vcgout" "./$exename" "$input" "$keyword"

# Kcachegrind
kcachegrind "$vcgout"

# cleanup
rm "$vcgout" "$exename"
