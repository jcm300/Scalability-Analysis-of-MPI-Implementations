#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int array[], int arraySize) {
	int i;
	// use current time as seed for random generator
	srand(time(0));
	for (i = 0; i < arraySize; i++) {
		array[i] = rand() % 100; //INT_MAX
	}
}

void boolean_test(){
    int N = 1000000;
    double startTime, endTime;
    int x[N];
    int y[N];
    int i=0, b;

    fillArray(x,N);
    fillArray(y,N);

    //Start timing
    startTime = omp_get_wtime();
    
    while(i<N){
        b = (x[i] < y[i]);
        i++;
    }

    //End timing
    endTime = omp_get_wtime() - startTime;
    printf("%f\n", endTime);
}

int main(){
    boolean_test();
    return 0;
}
