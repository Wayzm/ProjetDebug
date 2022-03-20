### Makefile
### Multiple version are implemented for the sake of optimisation

CC=gcc
INT= icc

### Compiler options
OPTC= -g -mavx2 -rdynamic

# Directories
INCH= -I ./include
INCS= ./src
INCB= ./bin

###

DEBUG = main.o
SFM = sfm.o
FPE = fpe.o
TLS = tools.o

###


all: bin/main bin/sfm bin/fpe

debg: bin/main

main.o: $(INCS)/main.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/main.c

sfm.o: $(INCS)/sfm.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/sfm.c

fpe.o: $(INCS)/fpe.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/fpe.c

tools.o: $(INCS)/tools.c
	$(CC) $(OPTC) -c $(INCH) $(INCS)/tools.c

### On veut le binaire des programmes ci dessous
bin/sfm: $(SFM)
	$(CC) -o sfm $(OPTC) $(SFM)

bin/fpe: $(FPE)
	$(CC) -o fpe $(OPTC) $(FPE)
###

bin/main: $(DEBUG) $(TLS)
	$(CC) -o debug $(OPTC) $(DEBUG) $(TLS)

debug:
	debug

test_sfm:
	bin/sfm

test_fpe:
	bin/fpe

clean:
	rm *.o  fpe sfm debug


