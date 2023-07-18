CC=gcc
CFLAGS=-Wall -pthread

all: threadarray pthreadstatcalc tokenid sudokuvalidator

threadarray: threadarray.c
	$(CC) $(CFLAGS) -o threadarray threadarray.c

pthreadstatcalc: pthreadstatcalc.c
	$(CC) $(CFLAGS) -o pthreadstatcalc pthreadstatcalc.c -lm

tokenid: tokenid.c
	$(CC) $(CFLAGS) -o tokenid tokenid.c

sudokuvalidator: sudokuvalidator.c
	$(CC) $(CFLAGS) -o sudokuvalidator sudokuvalidator.c

clean:
	rm -f threadarray pthreadstatcalc tokenid sudokuvalidator