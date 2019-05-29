#!/bin/sh
#
#PBS -N AP
#PBS -l walltime=60:00
#PBS -l nodes=2:r641:ppn=32
#PBS -q mei

module load gcc/5.3.0
module load gnu/openmpi_eth/2.0.0

cd MergeSort/MPI

rm AP.*
make clean
make

rm -rf times
mkdir times

SIZE=512
while [ $SIZE -lt 2049 ]; do
    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 65 ]; do
        NUM=0
        while [ $NUM -lt 15 ]; do
            mpirun --map-by node --oversubscribe -np $OMP_NUM_THREADS mergeSortMPI $SIZE >> times/mpi_$SIZE.txt
            mpirun --map-by node --oversubscribe -np $OMP_NUM_THREADS mergeSortCommOnly $SIZE >> times/comm_$SIZE.txt
            let NUM=NUM+1
        done
        let OMP_NUM_THREADS=$OMP_NUM_THREADS*2
    done
    let SIZE=$SIZE*2
done
