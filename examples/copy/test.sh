#!/bin/bash

infile="in/sample.txt"

for outfile in out/*; do
    DIFF=$(diff $infile $outfile)
    if [ "$DIFF" != "" ]; then
        printf "[FAILED] "
    else
        printf "[SUCCESS] "
    fi
    printf "diff $infile $outfile\n"
done
