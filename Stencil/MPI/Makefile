CC=mpic++
CFLAGS=-O3
SRC_DIR=src
BUILD_DIR=build
BIN_DIR=bin
MPI=stencil_mpi
DEPS=matrix_utils

SRC=$(wildcard $(SRC_DIR)/*.c)

.DEFAULT_GOAL = all

$(DEPS): $(wildcard $(SRC_DIR)/$(DEPS).[hcpp])

$(BIN_DIR)/$(MPI): $(SRC_DIR)/$(MPI).cpp $(DEPS)
	$(CC) $(CFLAGS) $(SRC_DIR)/$(MPI).cpp $(SRC_DIR)/$(DEPS).cpp
	mv a.out $(BIN_DIR)

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(MPI)

clean:
	rm -rf $(BUILD_DIR)/ $(BIN_DIR)/
