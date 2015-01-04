progs = test_gaussj test_gaussjbs test_ludcmp test_determinant test_tridiag test_inverse

CC = gcc
INCLUDES = -I$(SRC_DIR)/linalg/ -I$(SRC_DIR)/matrix/
CFLAGS = -Wall -g $(INCLUDES)

SRC_DIR := /home/alvaro/Repos/mad
MATRIX_OBJ := $(SRC_DIR)/matrix/matrix.o
PIVOTING_OBJ := $(SRC_DIR)/linalg/pivoting.o

DEPS_GAUSSJ := $(MATRIX_OBJ) $(SRC_DIR)/linalg/gaussj.o $(PIVOTING_OBJ)
DEPS_GAUSSJBS := $(MATRIX_OBJ) $(SRC_DIR)/linalg/gaussjbs.o $(PIVOTING_OBJ)
DEPS_LUDCMP := $(MATRIX_OBJ) $(SRC_DIR)/linalg/ludcmp.o $(PIVOTING_OBJ)
DEPS_DETERMINANT := $(DEPS_LUDCMP)
DEPS_TRIDIAG := $(MATRIX_OBJ) $(SRC_DIR)/linalg/tridiag.o
DEPS_INVERSE := $(DEPS_LUDCMP) $(SRC_DIR)/linalg/inverse.o

ALLDEPS = $(DEPS_GAUSSJ) $(DEPS_GAUSSJBS) $(DEPS_LUDCMP) $(DEPS_DETERMINANT) $(DEPS_TRIDIAG) $(DEPS_INVERSE)

all: $(progs)

test_gaussj: $(DEPS_GAUSSJ)

test_gaussjbs: $(DEPS_GAUSSJBS)

test_ludcmp: $(DEPS_LUDCMP)

test_determinant: $(DEPS_DETERMINANT)

test_tridiag: $(DEPS_TRIDIAG)

test_inverse: $(DEPS_INVERSE)

clean:
	rm $(sort $(progs) $(ALLDEPS))
