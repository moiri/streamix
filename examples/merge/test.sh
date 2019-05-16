#!/bin/bash

infile="in/sample1.txt"
outfile="out/out1.txt"

check_files()
{
    DIFF=$(diff $1 $2)
    if [ "$DIFF" != "" ]; then
        printf "[FAILED] "
    else
        printf "[SUCCESS] "
    fi
    printf "diff $1 $2\n"
}

check_files "in/sample1.txt" "out/out1.txt"
check_files "in/sample2.txt" "out/out2.txt"
