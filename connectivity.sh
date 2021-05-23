#!/bin/sh
#SBATCH -p short
#SBATCH -n64
#SBATCH -C beta
mpicc -o connectivity connectivity.c
mpirun connectivity -v