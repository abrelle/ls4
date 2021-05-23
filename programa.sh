#!/bin/sh
#SBATCH -p short
#SBATCH -n64
#SBATCH -C beta
g++ -o eratosthenes -fopenmp eratosthenes.cpp
mpirun ./eratosthenes 1000000