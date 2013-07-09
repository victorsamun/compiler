#!/bin/bash

./compiler $1.lang 2>$1.lasm
llc a.bc
gcc a.s
rm -f a.bc a.s
mv a.out $1

