progs = test_gaussj test_gaussjbs test_ludcmp test_determinant test_tridiag

CC = gcc
INCLUDES = -I$(SRC_DIR)/linalg/ -I$(SRC_DIR)/matrix/
CFLAGS = -Wall -g $(INCLUDES)

SRC_DIR := /home/alvaro/Repos/mad
MATRIX_OBJ := $(SRC_DIR)/matrix/matrix.o

DEPS_GAUSSJ = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/gaussj.o
DEPS_GAUSSJBS = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/gaussjbs.o
DEPS_LUDCMP = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/ludcmp.o
DEPS_DETERMINANT = $(DEPS_LUDCMP)
DEPS_TRIDIAG = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/tridiag.o

all: $(progs)

test_gaussj: $(DEPS_GAUSSJ)

test_gaussjbs: $(DEPS_GAUSSJBS)

test_ludcmp: $(DEPS_LUDCMP)

test_determinant: $(DEPS_DETERMINANT)

test_tridiag: $(DEPS_TRIDIAG)

clean:
	rm $(sort $(progs) $(DEPS_GAUSSJ) $(DEPS_GAUSSJBS))
