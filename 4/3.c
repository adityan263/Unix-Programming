#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <limits.h>

/* Driver program */
int main(int argc, char *argv[]) {

	struct tms t;
	times(&t);
	printf("Initially\n");
	printf("utime = %ld\n", t.tms_utime);
	printf("cutime = %ld\n", t.tms_cutime);
	printf("stime = %ld\n\n", t.tms_stime);
	pid_t pid;
	int i=0;
	if ((pid = fork()) == 0) {
		while(i++<1000000000);

		times(&t);
		printf("Before calling exec\n");
		printf("utime = %ld\n", t.tms_utime);
		printf("cutime = %ld\n", t.tms_cutime);
		printf("stime = %ld\n\n", t.tms_stime);
		char *param[] = {"./temp.o", NULL};
		execv("./temp.o", param);
		perror("");
	}
	else
		waitpid(pid, NULL, 0);
	return 0;
}
