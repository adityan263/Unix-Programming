#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigint_handler(int signo){
	printf("Parent: SIGINT caught with signo = %d\n", signo);
}

int main() {
	pid_t pid;
	
	if((pid = fork()) < 0) {
		printf("fork() error");
	}
	else if(pid == 0) {
		printf("Child: Sending SIGINT to parent(%d)\n", getppid());
		kill(getppid(), SIGINT);
		_exit(0);
	}
	else {
		signal(SIGINT, &sigint_handler);
		if(sleep(5) == 0) {
			printf("Parent: sleep(5) successful\n");
		}
		else {
			printf("Parent: sleep(5) interrupted\n");
		}
	}
	
	waitpid(pid, NULL, 0);
	
	return 0;
}
