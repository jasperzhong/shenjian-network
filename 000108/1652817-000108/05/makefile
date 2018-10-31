CC=gcc
target=tcp_server5-1 tcp_client5-1 tcp_server5-2 tcp_client5-2 tcp_server5-3 tcp_client5-3
all: $(target)
$(target): %: %.c
	$(CC) -o $@ $<

clean:
	rm -rf $(target) *.o
