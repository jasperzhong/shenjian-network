CC=gcc

test2: test2.c libtest1.so
	$(CC) -o $@ $< -L. -ltest1

libtest1.so: test1.c
	$(CC) -shared -fpic $< -o $@

clean:
	rm test2 *.so
