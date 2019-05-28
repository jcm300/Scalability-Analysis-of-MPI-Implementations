#include<stdlib.h>
#include<stdio.h>

#define M_SIZE 1024
#define ITERATIONS 512

#define STENCIL_P 4

void initiateMask(double *C);
void initiateMatrix(double m[M_SIZE][M_SIZE]);
void printResults(double m[M_SIZE][M_SIZE]);
