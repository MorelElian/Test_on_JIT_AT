#!/bin/sh

# Liste des valeurs de N
N="8 16 32 64 128 256 512 1024 2048 4096 8096"

for n in $N
do
  echo "Running block_matmul for N = $n"
  for i in $(seq 1 10)
  do
    ./block_matmul $n
  done
done