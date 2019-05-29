MPI    = mergeSortMPI
COMM   = mergeSortCommOnly
CC     = mpicc
CFLAGS = -Wall -ansi -pedantic -std=c99 
MPI_LFLAGS = -lm -o $(MPI)
COMM_LFLAGS = -lm -o $(COMM)

default: all

$(MPI): $(MPI).c
	$(CC) $(CFLAGS) $(MPI).c $(MPI_LFLAGS)

$(COMM): $(COMM).c
	$(CC) $(CFLAGS) $(COMM).c $(COMM_LFLAGS)

all: $(COMM) $(MPI)

clean:
	rm -f $(MPI) $(COMM)
