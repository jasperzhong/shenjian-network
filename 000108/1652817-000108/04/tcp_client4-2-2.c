// Client side C program
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_SIZE 1024

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
	
	const char* str = "zhongyuchenzhongyuchenzhongyuchen";
	
	int i;
	for (i = 0; i < 10; ++i) {
		strncpy(buffer, str + i*2, 2);	
		printf("准备发送%dbytes\n", strlen(buffer));
		int write_len = send(sock, buffer, strlen(buffer), 0);
		if(write_len < 0){
			perror("发送失败\n");	
			break;
		}
		printf("已发送%dbytes\n", write_len);
		sleep(1);
		printf("sleep\n");
	}
	

	close(sock);
	return 0;
	
}
