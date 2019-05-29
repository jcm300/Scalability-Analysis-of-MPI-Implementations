#!/bin/sh
#
#PBS -N AP
#PBS -l walltime=60:00
#PBS -l nodes=1:r641:ppn=32
#PBS -q mei

module load gcc/5.3.0

cd MergeSort/SEQ

rm AP.*
make clean
make

rm -rf times
mkdir times

SIZE=512
while [ $SIZE -lt 2049 ]; do
    NUM=0
    while [ $NUM -lt 15 ]; do
        ./mergeSortSeq $SIZE >> times/mergesort_$SIZE.txt
        let NUM=NUM+1
    done
    let SIZE=$SIZE*2
done
