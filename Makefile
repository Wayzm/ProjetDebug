### Makefile
### Multiple version are implemented for the sake of optimisation

CC=gcc
INT= icc

### Compiler options
OPTC=-Ofast -fopenmp  -mavx2

# Directories
INCH= -I ./include
INCS= ./src
INCB= ./bin

###

DEBUG = main.o
SFM = sfm.o
FPE = fpe.o

###


all: bin/main bin/sfm bin/fpe

debg: bin/main

main.o: $(INCS)/main.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/main.c

sfm.o: $(INCS)/sfm.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/sfm.c

fpe.o: $(INCS)/fpe.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/fpe.c

### On veut le binaire des programmes ci dessous
bin/sfm: $(SFM)
	$(CC) -o $(INCB)/sfm $(OPTC) $(SFM)

bin/fpe: $(FPE)
	$(CC) -o $(INCB)/fpe $(OPTC) $(FPE)
###

bin/main: $(DEBUG)
	$(CC) -o $(INCB)/main $(OPTC) $(DEBUG)

debg:
	bin/main

clean:
	rm *.o bin/*
