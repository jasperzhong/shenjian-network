CC=gcc
target: tcp_server1 tcp_client1
tcp_server1: tcp_server1.o
	$(CC) -o $@ $<
tcp_client1: tcp_client1.o
	$(CC) -o $@ $<
clean:
	rm -rf *.o tcp_server1 tcp_client1
