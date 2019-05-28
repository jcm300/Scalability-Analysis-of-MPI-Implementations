#!/bin/sh
#
#PBS -N AP
#PBS -l walltime=90:00
#PBS -l nodes=2:r641:ppn=32
#PBS -q mei

module load gcc/5.3.0

cd Stencil/SEQ

rm Teste.*
mkdir times

SIZE=512
while [ $SIZE -lt 2049 ]; do
    sed "s/#define M_SIZE.*/#define M_SIZE $SIZE/g" -i src/matrix_utils.h
    
    make clean
    make

    NUM=0
    while [ $NUM -lt 15 ]; do
        bin/stencil_seq >> times/seq_res_stencil_$SIZE.txt
        let NUM=NUM+1
    done
    let SIZE=$SIZE*2
done
