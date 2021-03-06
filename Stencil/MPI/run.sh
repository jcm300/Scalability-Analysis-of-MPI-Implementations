#!/bin/sh
#
#PBS -N AP
#PBS -l walltime=90:00
#PBS -l nodes=2:r641:ppn=32
#PBS -q mei

module load gcc/5.3.0
module load gnu/openmpi_eth/2.0.0

cd Stencil/MPI

rm Teste.*
mkdir times

SIZE=512
while [ $SIZE -lt 2049 ]; do
    sed "s/#define M_SIZE.*/#define M_SIZE $SIZE/g" -i src/matrix_utils.hpp
    
    make clean
    make

    OMP_NUM_THREADS=2
    while [ $OMP_NUM_THREADS -lt 65 ]; do
        NUM=0
        while [ $NUM -lt 15 ]; do
            mpirun --map-by node --oversubscribe -np $OMP_NUM_THREADS bin/a.out >> times/mpi_res_stencil_$SIZE.txt
            let NUM=NUM+1
        done
        let OMP_NUM_THREADS=$OMP_NUM_THREADS*2
    done
    let SIZE=$SIZE*2
done
