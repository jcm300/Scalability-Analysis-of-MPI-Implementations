#include "matrix_utils.h"

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
