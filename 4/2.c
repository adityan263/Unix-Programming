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

#define MAX 256

int main(int argc, char *argv[]) {
	
	pid_t pid;
	if (argc != 2) {
		printf("Usage: ./a.out <filename>");
		return errno;
	}
	int fd = open(argv[1], O_RDONLY);
	char cmd[MAX];

	if ((pid = fork()) == 0) {
		int len = read(fd, cmd, MAX);
		cmd[len]= '\0';
		system(cmd);
	}
	else {
		sleep(1);
	}
	return 0;
}
