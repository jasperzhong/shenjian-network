CC=gcc
CFLAGS=-I.
DEPS=test.h
OBJ=test1.o test2.o test3.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm test *.o
