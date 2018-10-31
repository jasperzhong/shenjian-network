CC=gcc
target=tcp_server6-1 tcp_client6-1 tcp_server6-2 tcp_client6-2 tcp_server6-3 tcp_client6-3 tcp_server6-4 tcp_client6-4
all: $(target)
$(target): %: %.c
	$(CC) -o $@ $<

clean:
	rm -rf $(target) *.o
