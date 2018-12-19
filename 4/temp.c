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

/* called execv */
int main(int argc, char *argv[]) {

	struct tms t;
	times(&t);
	printf("After calling exec\n");
	printf("utime = %ld\n", t.tms_utime);
	printf("cutime = %ld\n", t.tms_cutime);
	printf("stime = %ld\n", t.tms_stime);
	return 0;
}
