CC=g++
CCXFLAGS=-g -std=c++14 -Wall

OBJS= src/main.o src/number.o src/bigint2.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o p3 ${OBJS}

.PHONY: clean

run: all
	./p3 input.txt
	
clean: 
	rm -rf src/*.o p3 output.txt