#!/bin/bash
clang++ -fjit -O3 ../Selecting_matmul.cpp -o ../bin/selecting_matmul
echo -e "N;i;id_matmul;time_recorded\n" > ../data/trace_selecting_matmul.csv
J="4 8 16 32 64 128 150 200 256"
for j in $J
do
for i in $(seq 1 50)
do
    ../bin/selecting_matmul $j
done
done
