#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syslog.h>
void create_deamon(){
	// fork off the parent process
	pid_t pid = fork();
	if(pid < 0){
		exit(EXIT_FAILURE);
	}
	
	// exit the parent process
	if(pid > 0){
		exit(EXIT_SUCCESS); 
	}
	
	// create a new sid for the child process
	pid_t sid = setsid();
	if (sid < 0){
		exit(EXIT_FAILURE);
	}

	
	pid = fork();
	
	if(pid < 0){
		exit(EXIT_FAILURE);
	}
	
	if(pid > 0){
		exit(EXIT_SUCCESS);
	}
	
	// set new file permissions
	umask(0);	

	// change the current working directory
	if((chdir("/")) < 0){
		exit(EXIT_FAILURE);
	}
	
	// close out the standard file descriptors
	/*	
	int x;
	for(x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
		close(x);
	
	openlog("zyc_daemon", LOG_PID, LOG_DAEMON);*/
}

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage: ./test4-1 number\n");
		exit(EXIT_FAILURE);
	}
	int n = atoi(argv[1]);
	//printf("loop %d times\n", n);

	create_deamon();
	
	int i;
	int fork_num = 0;
	int recycle_num = 0;
	pid_t pid;
	pid_t max_pid = 1;
	for (i = 0;i < n; ++i){
		pid = fork();
		
		// loop until fork sucessfully
		while(pid < 0){			
			sleep(1);
			//printf(".");
			pid = fork();
		}
		++fork_num;
		if(pid > max_pid)
			max_pid = pid;
		
		// child 
		if (pid == 0){
			char str[1024];
			str[0] = 'z';
			str[511] = 'y';
			str[1023] = 'c';

			sleep(1);
			exit(EXIT_SUCCESS);
		}

		if(fork_num % 1000 == 0){
			while(waitpid(-1, NULL, WNOHANG) > 0)
				recycle_num++;
			printf("已分裂%d个子进程\n", i+1);
			printf("分裂进程数:%d, 回收进程数%d\n", fork_num, recycle_num);
			sleep(3);
		}
	}

	printf("成功分裂%d个子进程\n", i);
	printf("最大进程号为%d\n", max_pid);
	fflush(stdout);
	while(1){
		while(waitpid(-1, NULL, WNOHANG) > 0)
			recycle_num++;
		printf("分裂进程数:%d, 回收进程数%d\n", fork_num, recycle_num);
		sleep(5);		
	}	
}
