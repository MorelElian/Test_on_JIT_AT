clang++ -fjit -O3 Selecting_matmul.cpp -o selecting_matmul
for ((i=1; i<=100; i++))
do
    ./selecting_matmul 10
done
