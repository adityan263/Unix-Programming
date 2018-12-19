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
#include <limits.h>

int main(int argc, char *argv[]) {

	int pipe_d[2];
	pid_t pid;
	if (pipe(pipe_d) < 0) {
		perror("Can't open pipe");
		exit(1);
	}
	
	if((pid == fork()) == 0) {
		close(pipe_d[1]);
		dup2(pipe_d[0], 0);
		printf("Output of ls -l | wc -l:\t");
		fflush(stdout);				    //else printf will print after output of command
		execlp("wc", "wc", "-l", NULL);
	}
	else {
		close(pipe_d[0]);
		dup2(pipe_d[1], 1);
		execlp("ls", "ls", "-l", NULL);
	}
	return 0;
}
