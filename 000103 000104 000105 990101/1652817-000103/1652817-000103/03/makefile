CC=gcc
TARGET=test1 test2 test3
all: $(TARGET)
$(TARGET): % : %.c
	$(CC) -o $@ $<
clean:
	rm test? 
