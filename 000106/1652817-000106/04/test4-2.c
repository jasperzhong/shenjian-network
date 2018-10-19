#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/prctl.h>
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

	signal(SIGCHLD, SIG_IGN);
	
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
int main(){
	create_deamon();
	
	int i;
	for (i = 0;i < 10; ++i){
		pid_t pid = fork();
		if (pid == 0){
			prctl(PR_SET_PDEATHSIG, SIGHUP);
				
			while(1){
				printf("%d %d 1652817 sub\n",(int)getppid(), (int)getpid());
				sleep(15);
			}
			exit(EXIT_SUCCESS);
		}
		sleep(3);
	}
	
		
	while(1){
		printf("%d %d 1652817 main\n", (int)getppid(), (int)getpid());
		sleep(5);
	}
}
