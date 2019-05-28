#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define M_SIZE 895
#define STENCIL_P 4

#define ITERATIONS 256
void initiateMask(double *C);
void initiateMatrix(double m[M_SIZE][M_SIZE]);
void printResults(double m[M_SIZE][M_SIZE]);
void copy(double *temp, int orig_offset, double *g, int dest_offset, int rows);
