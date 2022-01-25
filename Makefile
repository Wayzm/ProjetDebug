### Makefile
### Multiple version are implemented for the sake of optimisation

CC=gcc
INT= icc

### Compiler options
OPTC=-Ofast -fopenmp  -mavx2

# Directories
INCH= ./include
INCS= ./src
INCB= ./bin

###
###
###
###

DEBUG= main.o

###
###
###

all: bin/main


main.o: $(INCS)/main.c
	$(CC) $(OPTC) -c $(INCS)/main.c


bin/main: $(DEBUG)
	$(CC) -o $(INCB)/main $(OPTC) $(DEBUG)


gcc:
	bin/main

clean:
	rm *.o bin/*
