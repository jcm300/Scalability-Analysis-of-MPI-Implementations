#!/bin/sh
#
#PBS -N AP
#PBS -l walltime=60:00
#PBS -l nodes=1:r641:ppn=32
#PBS -q mei

module load gcc/5.3.0

gcc -std=c99 -fopenmp boolean_test.c

./a.out > time.txt
