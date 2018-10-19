CC=gcc
TARGET=test1-1 test1-2
all: $(TARGET)
$(TARGET): %: %.c
	$(CC) -o $@ $<

clean:
	rm  $(TARGET)
