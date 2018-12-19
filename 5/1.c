#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	
	pid_t pid;
	int i;
	pid = fork();
	if(pid < 0) {
		printf("fork error");
		return 0;
	}
	else if(pid == 0) {
		printf("child before setting foreground\n");
		system("ps -o pid,ppid,pgrp,tpgid,session,cmd");
		setpgid(0, 0);
		sleep(2);
		printf("\nchild:\nprintf working, enter any number:");
		scanf("%d",&i);
		printf("scanf working, you entered:%d\n",i);
		if(tcsetpgrp(STDIN_FILENO, getpgid(getppid())) != 0) {
			printf("could not make parent group a foreground process group\n");
			_exit(0);
		}
		_exit(0);
	}
	else {
		sleep(1);
		if(tcsetpgrp(open("/dev/tty",O_RDWR), getpgid(pid)) != 0) {
			printf("could not make child group a foreground process group\n");
			exit(0);
		}
	}
	wait(NULL);
	printf("\nparent:\nprintf working, enter any number:");
	scanf("%d",&i);
	printf("scanf working, you entered:%d\n",i);
	return 0;

}
