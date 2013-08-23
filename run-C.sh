#!/bin/bash

#export a random number for the RNG seed.
export GSL_RNG_SEED=$(head -1 /dev/urandom |od -N 10 |awk '{print $2}')

#run the executable with the input file
./SDE.out $1 $2
