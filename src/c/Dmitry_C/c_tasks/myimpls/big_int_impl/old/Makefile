CC = gcc
CFLAGS = -g -Wall

test: bigint.c test_bigint.c
	$(CC) -o mainbin bigint.c test_bigint.c $(CFLAGS)

clean:
	rm -f *.o mainbin
