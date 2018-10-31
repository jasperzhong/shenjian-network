// Client side C program
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	
	if(argc != 4) {
		perror("Usage: ./tcp_client client_port ip server_port\n");
		exit(EXIT_FAILURE);
	}
	int port = atoi(argv[3]);
	int client_port = atoi(argv[1]);
	struct sockaddr_in address, serv_addr, client_addr;
	int sock = 0, valread;
	char buffer[BUFFER_SIZE] = {0};

	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket failed\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	memset(&client_addr, 0, sizeof(client_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(client_port);	
	client_addr.sin_addr.s_addr = inet_addr("192.168.159.23");
	
	if(bind(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0){
		perror("bind error");
		exit(EXIT_FAILURE);
	}	
	
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("connection failed\n");	
		exit(EXIT_FAILURE);
	}
	printf("成功连接\n");
		
	// recv
	valread = recv(sock, buffer, sizeof(buffer), 0);
	
	close(sock);
	return 0;
	
}
