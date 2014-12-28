SRC_DIR := /home/alvaro/Repos/mad/

progs = test_gaussj test_gaussj_bs

CC = gcc

INCLUDES = -I$(SRC_DIR)/linalg/ -I$(SRC_DIR)/matrix/
CFLAGS = -Wall -g $(INCLUDES)

DEPS_GAUSSJ = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/gaussj.o
DEPS_GAUSSJBS = $(SRC_DIR)/matrix/matrix.o $(SRC_DIR)/linalg/gaussjbs.o

all: $(progs)

test_gaussj: $(DEPS_GAUSSJ)

test_gaussj_bs: $(DEPS_GAUSSJBS)

clean:
	rm $(progs)
