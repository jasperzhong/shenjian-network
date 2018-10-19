CC=gcc
TARGET=test4-1 test4-2
all: $(TARGET)
$(TARGET): %: %.c
	$(CC) -o $@ $<

clean:
	rm  $(TARGET)
