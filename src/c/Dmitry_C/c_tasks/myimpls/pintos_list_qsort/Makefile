CC = gcc
CFLAGS = -g -Wall

test: list.c test_list.c sort.c Source.c
	$(CC) -o mainbin list.c test_list.c sort.c Source.c $(CFLAGS)

clean:
	rm -f *.o mainbin
