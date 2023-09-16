CC = gcc
CFLAGS = -g -Wall

test_sort: listimpl.c sort.c test_sort.c
	$(CC) -o test_sort listimpl.c sort.c test_sort.c $(CFLAGS)
	./test_sort

test_listimpl: listimpl.c test_listimpl.c
	$(CC) -o test_listimpl listimpl.c test_listimpl.c $(CFLAGS)
	./test_listimpl

clean:
	rm -f *.o test_listimpl test_sort
