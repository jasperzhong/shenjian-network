CC=gcc
TARGET=test5-1 test5-2 test5-3
all: $(TARGET)
$(TARGET): %: %.c
	$(CC) -o $@ $<

clean:
	rm  $(TARGET)
