CC=gcc
TARGET=test3-1 test3-2
all: $(TARGET)
$(TARGET): %: %.c
	$(CC) -o $@ $<

clean:
	rm  $(TARGET)
