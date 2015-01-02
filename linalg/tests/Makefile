SRC_DIR := /home/alvaro/Repos/mad/

progs = test_gaussj test_gaussjbs test_ludcmp

CC = gcc

INCLUDES = -I$(SRC_DIR)/linalg/ -I$(SRC_DIR)/matrix/
CFLAGS = -Wall -g $(INCLUDES)

DEPS_GAUSSJ = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/gaussj.o
DEPS_GAUSSJBS = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/gaussjbs.o
DEPS_LUDCMP = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/ludcmp.o

all: $(progs)

test_gaussj: $(DEPS_GAUSSJ)

test_gaussjbs: $(DEPS_GAUSSJBS)

test_ludcmp: $(DEPS_LUDCMP)

clean:
	rm $(progs) $(DEPS_GAUSSJ) $(DEPS_GAUSSJBS)
