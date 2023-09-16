CC = gcc
CFLAGS = -g -Wall

test: listimpl.c test_listimpl.c sort.c Source.c
	$(CC) -o mainbin listimpl.c test_listimpl.c sort.c Source.c $(CFLAGS)

clean:
	rm -f *.o mainbin
