#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigint_handler(int signo){
	printf("Interrupt caught by parent signo = %d\n", signo);
}

void sigint_handler2(int signo){
	printf("Interrupt caught by child signo = %d\n", signo);
}

int main() {

	sigset_t newmask, oldmask;
	pid_t pid;

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	kill(getpid(), SIGINT);
	if((pid = fork()) < 0) {
		perror("fork() error");
		return 0;
	} 
	else if(pid == 0) {

		signal(SIGINT, &sigint_handler2);
		sigprocmask(SIG_BLOCK, NULL, &newmask);
		if(sigismember(&newmask, SIGINT)) {
			printf("Child inherits signal mask\n");
		}

		sigpending(&newmask);
		if(sigismember(&newmask, SIGINT)) {
			printf("Child inherits pending signals\n");
		}
		else {
			printf("Child doesn't inherit pending signals\n");
		}
	}
	else {
		signal(SIGINT, &sigint_handler);
	}

	sigprocmask(SIG_SETMASK, &oldmask, NULL);

	if(!pid) {
		_exit(0);
	}
	waitpid(pid, NULL, 0);
	return 0;
}
