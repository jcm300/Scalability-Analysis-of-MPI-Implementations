#include "matrix_utils.hpp"

void initiateMask(double *C){
    C[0]=5.f;
    C[1]=-1.f;
    C[2]=0.f;
    C[3]=-1.f;
    C[4]=0.f;
}

void initiateMatrix(double m[M_SIZE][M_SIZE]){
    for(int i=0; i<M_SIZE; i++)
        for(int j=0; j<M_SIZE; j++)
            m[i][j]=1.f;
}

void printResults(double m[M_SIZE][M_SIZE]){
    for(int i=0; i<M_SIZE; i++){
        for(int j=0; j<M_SIZE; j++)
            printf("%15.4f \t",m[i][j]);
        printf("\n");
    }
}

void copy(double *temp, int orig_offset, double *g, int dest_offset, int rows){
    for(int i=0; i<rows; i++)
        for(int j=0; j<M_SIZE; j++)
            *(g+(i+dest_offset)*M_SIZE+j) = *(temp+(i+orig_offset)*M_SIZE+j);
}
