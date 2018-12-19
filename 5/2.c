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
	if(pid < 0){
		printf("fork error");
		return 0;
	}
	else if(pid == 0){
		sleep(1);

		printf("running exec\n");
		execlp("ls","ls", "-l", NULL);
		sleep(2);
		_exit(0);
	}
	else{
		printf("before setpgid\n");
		printf("pid: %d, pgid : %d\n\n",pid, getpgid(pid));
		if(setpgid(pid, 0) == -1) {
			printf("\nafter exec\n");
			printf("Error, can't change pgid\n");
		}
		printf("after setpgid\n");
		printf("pid: %d, pgid : %d\n\n",pid, getpgid(pid));
		sleep(2);

		if(setpgid(pid, pid) == -1){
			printf("\nafter exec\n");
			printf("Error, can't change pgid\n");
		}
	}
	waitpid(pid, NULL, WUNTRACED);
	return 0;

}
