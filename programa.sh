#!/bin/sh
#SBATCH -p short
#SBATCH -n64
#SBATCH -C beta
mpic++ concurrent_eratosthenes.cpp -o concurrent_eratosthenes
mpirun ./concurrent_eratosthenes 1000000
