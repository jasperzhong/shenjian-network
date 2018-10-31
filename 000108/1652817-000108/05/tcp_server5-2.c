// Server side C program
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define QUEUE  5
#define BUFFER_SIZE 21000

int main(int argc, char *argv[]){
	if(argc != 3){
		perror("Usage: ./tcp_server ip port\n");
		exit(EXIT_FAILURE);
	}
	int port = atoi(argv[2]);
			
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};
	
	// Create socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the given port
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0) {
		perror("setsockopt failed");
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(argv[1]);
	address.sin_port = htons(port);
	
	
	// Forcefully attaching socket to the given port
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, QUEUE) < 0) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
			(socklen_t *)&addrlen)) < 0) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
		
	struct sockaddr_in client;
	socklen_t client_len = sizeof(client);
	getpeername(new_socket, (struct sockaddr*)&client, &client_len);
	printf("成功连接, client IP:%s Port:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));	
	
	int cnt = 0, i = 0;
	// read 20 bytes
	while(1){
		for(i = 0;i < 20000; ++i)
			buffer[i] = '1';
		buffer[i] = '0';
		valread = write(new_socket, buffer, 20000);	
		if(valread < 0)
			perror("Error reading from socket");
		else{
			cnt += valread;
			printf("累计已发送%dbytes\n", cnt);
		}
		sleep(1);	
	}
	close(new_socket);
	close(server_fd);
	return 0;
}
