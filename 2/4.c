#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

void print_times(char* a) {
	struct stat buf;
	stat(a, &buf);
	printf("Last change:       %s", ctime(&buf.st_ctime));
	printf("Last access:       %s", ctime(&buf.st_atime));
	printf("Last modification: %s", ctime(&buf.st_mtime));
}

int main() {
	char file[] = "q4.txt";
	char str[] = "hello";
	int f = creat(file, 0600);
	print_times(file);
	sleep(1);

	printf("\nopen:\n");
	f = open(file, O_RDWR);
	print_times(file);
	sleep(1);

	printf("\nwrite:\n");
	write(f, str, 5);
	print_times(file);
	sleep(1);

	printf("\nread:\n");
	read(f, str, 5);
	print_times(file);
	sleep(1);

	printf("\naccess:\n");
	access(file, R_OK | W_OK | X_OK);
	print_times(file);
}
