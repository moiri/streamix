#!/bin/bash

infile="in/res.txt"
outfile="out/out.txt"

DIFF=$(diff $infile $outfile)
if [ "$DIFF" != "" ]; then
    printf "[FAILED] "
else
    printf "[SUCCESS] "
fi
printf "diff $infile $outfile\n"
