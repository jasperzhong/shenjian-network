#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/prctl.h>

#define MAX_N 50
int cnt = 1;
int child_alive[MAX_N];  // record whether sub process is alive
int child_pid[MAX_N]; // record pid of each sub process

void func_waitpid(int signo){
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0){
		cnt--;
		int i;
		for(i = 1;i < MAX_N; i++)
			if(child_pid[i] == pid)
				break;
		child_alive[i] = 0;
	}
}

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
	/*
	pid_t sid = setsid();
	if (sid < 0){
		exit(EXIT_FAILURE);
	}*/

	// signal(SIGCHLD, SIG_IGN);
	
		
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
	create_deamon();
	signal(SIGCHLD, &func_waitpid);
	
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);

	char buf[100];
		
	int n = read_conf();
	int sec, min, hr;
	int i,j;
	while(1){
		clock_gettime(CLOCK_REALTIME, &end);
		sec = end.tv_sec - start.tv_sec;
		min = sec / 60;
		hr = min / 60;
		sprintf(buf, "./test [main %02d:%02d:%02d]", hr%24, min%60, sec%60);
		strcpy(argv[0], buf);
		sprintf(buf, "./test [main]");
		prctl(PR_SET_NAME, buf);  
		if(cnt <= n){
			for(i = 1;i < MAX_N; ++i)
				if(child_alive[i] == 0)
					break;
			j = i;
			child_alive[j] = 1;	
			pid_t pid = fork();
			if(pid == 0){
				prctl(PR_SET_PDEATHSIG, SIGHUP);
				struct timespec pstart, pend;
				clock_gettime(CLOCK_REALTIME, &pstart);
				int psec, pmin, phr;
				char cnt_buf[100];
				while(1){
					clock_gettime(CLOCK_REALTIME, &pend);
					psec = pend.tv_sec - pstart.tv_sec;
					pmin = psec / 60;
					phr = pmin / 60;
					sprintf(cnt_buf, "./test [sub-%02d %02d:%02d:%02d]",j, phr%24, pmin%60, psec%60); 
					
					strcpy(argv[0], cnt_buf);
					sprintf(cnt_buf, "./test [sub-%02d]", cnt);
					prctl(PR_SET_NAME, cnt_buf);
					sleep(1);
				}
			}
			++cnt;
			child_pid[j] = pid;
		}
		sleep(1);
	}	
		
}
