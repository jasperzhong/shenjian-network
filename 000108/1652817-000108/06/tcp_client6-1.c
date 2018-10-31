// Client side C program
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	
	if(argc != 5) {
		perror("Usage: ./tcp_client ip port read_size write_size\n");
		exit(EXIT_FAILURE);
	}
	int port = atoi(argv[2]);
		
	struct sockaddr_in address, serv_addr;
	int sock = 0;
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
	int valread, valwrite;
	int read_cnt = 0, write_cnt = 0, i = 0;
	int read_size = atoi(argv[3]);
	int write_size = atoi(argv[4]);

	while(1){
		  valread = read(sock, buffer, read_size);
                  if(valread < 0)
                          perror("Error reading from socket");
                  else{
                          read_cnt += valread;
                          printf("累计已读取%dbytes\n", read_cnt);
                  }
                  // sleep(1);    
  
                  valwrite = write(sock, buffer, write_size);
                  if(valwrite < 0)
                         perror("Error writing from socket");
                  else{
                          write_cnt += valwrite;
                          printf("累计已读取%dbytes\n", write_cnt);
                  }
	}

	close(sock);
	return 0;
	
}
