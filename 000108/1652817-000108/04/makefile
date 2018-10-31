CC=gcc
target=tcp_server4-1 tcp_client4-1-1 tcp_client4-1-2 tcp_server4-2 tcp_client4-2-1 tcp_client4-2-2
all: $(target)
$(target): %: %.c
	$(CC) -o $@ $<

clean:
	rm -rf $(target) *.o
