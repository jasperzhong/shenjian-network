// Client side C program
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_SIZE 21000

int main(int argc, char *argv[]){
	
	if(argc != 3) {
		perror("Usage: ./tcp_client ip port\n");
		exit(EXIT_FAILURE);
	}
	int port = atoi(argv[2]);
		
	struct sockaddr_in address, serv_addr;
	int sock = 0, valread;
	char buffer[BUFFER_SIZE] = {0};

	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket failed\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
		
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		perror("connection failed\n");	
		exit(EXIT_FAILURE);
	}
	
	printf("成功连接\n");
	getchar();
	int read_len;
	int cnt = 0, i = 0;
	while(1){
		read_len = read(sock, buffer, 10000);
		cnt += read_len;
		printf("累计已接收%dbytes\n", cnt);
		sleep(1);
	}

	close(sock);
	return 0;
	
}
