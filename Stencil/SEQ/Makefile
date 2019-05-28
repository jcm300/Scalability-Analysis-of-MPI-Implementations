CC=gcc
CFLAGS=-O3 -std=c99
SRC_DIR=src
BUILD_DIR=build
BIN_DIR=bin
SEQ=stencil_seq
DEPS=matrix_utils
OS:= $(shell uname -s)


ifeq ($(OS), Darwin)
	CFLAGS += -Xpreprocessor -fopenmp -lomp
else
	CFLAGS += -fopenmp
endif

SRC=$(wildcard $(SRC_DIR)/*.c)

.DEFAULT_GOAL = all

$(DEPS): $(wildcard $(SRC_DIR)/$(DEPS).[hc])

$(BIN_DIR)/$(SEQ): $(SRC_DIR)/$(SEQ).c $(DEPS)
	$(CC) $(CFLAGS) $(SRC_DIR)/$(SEQ).c $(SRC_DIR)/$(DEPS).c -o $(SEQ)
	mv $(SEQ) $(BIN_DIR)

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(SEQ)

clean:
	rm -rf $(BUILD_DIR)/ $(BIN_DIR)/
