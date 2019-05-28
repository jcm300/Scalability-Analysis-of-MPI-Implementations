#!/bin/bash
cat times/mpi_res_mergesort_$1.txt | ggrep -i sorting | cut -d ' ' -f 5 > mergesort_$1_raw.txt

gawk -f res_proc.awk mergesort_$1_raw.txt > mergesort_$1_stats.txt

rm mergesort_$1_raw.txt
