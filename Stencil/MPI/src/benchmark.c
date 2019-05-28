#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define VEC_SIZE 1000
#define PIVOT VEC_SIZE/2
#define SAMPLE_SIZE 10000
#define STENCIL_P 4

double latency_test(MPI_Status status, int rank){
    double avg_time = 0.f;

    MPI_Barrier(MPI_COMM_WORLD);
    
    if(!rank)
        avg_time =  MPI_Wtime();
    for(int i = 0; i < SAMPLE_SIZE; i++){
        if(!rank){
            MPI_Send(NULL, 0, MPI_INT, 1, 1, MPI_COMM_WORLD);
            MPI_Recv(NULL, 0, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
        }else{
            MPI_Recv(NULL, 0, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Send(NULL, 0, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }    
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    if(!rank)
        avg_time = MPI_Wtime() - avg_time;

    avg_time = avg_time/SAMPLE_SIZE*1.0e6;
    return avg_time/2;                          // half round trip
}

double throughput_test(double latency, MPI_Status status, int rank){
    double avg_time = 0.f;
    double *vec = (double*)calloc(VEC_SIZE, sizeof(double));
    
    MPI_Barrier(MPI_COMM_WORLD);

    if(!rank)
        avg_time = MPI_Wtime();
    for(int i = 0; i < SAMPLE_SIZE; i++){
        if(!rank){
            MPI_Send(vec, VEC_SIZE, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
            MPI_Recv(vec, VEC_SIZE, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
        }else{
            MPI_Recv(vec, VEC_SIZE, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
            MPI_Send(vec, VEC_SIZE, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if(!rank)
        avg_time = MPI_Wtime() - avg_time;
    avg_time = avg_time/SAMPLE_SIZE*1.0e6-2*latency;

    return avg_time/(2*VEC_SIZE*sizeof(double));
}

void initiateMask(double *C){
    C[0]=5.f;
    C[1]=-1.f;
    C[2]=0.f;
    C[3]=-1.f;
    C[4]=0.f;
}

double computation_test(int rank){
    double avg_time=0.f;
    double *vec = (double*)malloc(VEC_SIZE*sizeof(double));
    double c[5];
    initiateMask(c);

    MPI_Barrier(MPI_COMM_WORLD);

    if(!rank)
        avg_time = MPI_Wtime();
    for(int i = 0; i < SAMPLE_SIZE; i++){
        vec[PIVOT] = vec[PIVOT]*c[0];
        for(int w = 1; w <= STENCIL_P; w ++)
            vec[PIVOT] += c[w]*vec[PIVOT+w] + c[w]*vec[PIVOT-w];
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if(!rank)
        avg_time = MPI_Wtime() - avg_time;
    avg_time = avg_time/SAMPLE_SIZE*1.0e6;

    return avg_time/17;             //no. of ops: additions + multiplications (loops and indexing are not taken into account)
}

int main(int argc, char *argv[]){
    int rank, no_procs;
    double ts, tw, tc;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &no_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    ts = latency_test(status, rank);
    tw = throughput_test(ts, status, rank);
    tc = computation_test(rank);

    MPI_Finalize();
    if(!rank){
        printf("ts: %12.8f us \n", ts); 
        printf("1/tw: %12.8f us/byte\n", tw); 
        printf("tc: %12.8f us/op\n", tc); 
    }
}