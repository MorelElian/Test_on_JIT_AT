#!/bin/bash
clang++ -fjit ../basic_Autotuning.cpp ../bin/basic_autotuning
# Boucle pour exécuter 100 fois la commande

for ((i=1; i<=100; i++))
do
    ./basic_autotuning 10
done
