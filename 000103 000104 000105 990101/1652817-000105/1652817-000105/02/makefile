CC=g++

test2: test2.cpp libtest1.so
	$(CC) -o $@ $< -L. -ltest1

libtest1.so: test1.cpp
	$(CC) -shared -fpic $< -o $@

clean:
	rm test2 *.so
