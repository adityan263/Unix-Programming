#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>

int main(int argc, char *argv[]){

	int status, i, pid;
	if(argc != 4) {
		errno = 1;
		printf("Usage: ./a.out <num_threads> <sleeptime_parent> <sleeptime_child>");
		exit(errno);
	}
	int n = atoi(argv[1]), st_child = atoi(argv[2]), st_parent = atoi(argv[3]);

	pid_t pids[n];
	for(i = 0; i < n; i++) {
		if ((pids[i] = fork()) == 0) {
			sleep(st_child);
			exit(0);
		}
	}
	sleep(st_parent);

	for(i = 0; i < n; i++) {
		pid = waitpid(pids[i], &status, WNOHANG);
		printf("child with PID=%d ", pids[i]);
		if(pid != 0) {
			if(WIFEXITED(status))
				printf("Normal termination, exit status=%d\n", WEXITSTATUS(status));
			else if(WIFSIGNALED(status))
				printf("Termination with signal number=%d \n", WTERMSIG(status));
		}
		else {
			printf("Still running, i=%d\n", i);
		}
	}
	return 0;
}
