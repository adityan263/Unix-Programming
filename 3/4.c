#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 256

void print_all_env(FILE* f) {
	extern char** environ;
	int i = 0;
	while(environ[i] != NULL) {
		fprintf(f, "%2d) %s\n", i+1, environ[i]);
		i++;
	}
}

int main(int argc, char *argv[], char *envp[]) {

	FILE* f1 = fopen("1.txt", "w");
	FILE* f2 = fopen("2.txt", "w");
	FILE* f3 = fopen("3.txt", "w");
	FILE* f4 = fopen("4.txt", "w");
	FILE* f5 = fopen("5.txt", "w");
	print_all_env(f1);
	char str[]="aditya=2", str1[] = "aditya", str2[] = "neralkar";
	char val[]="5", val1[] = "8";

	if(putenv(str)) {
		errno = 1;
		perror("Couldn't add to variable1");
	}
	print_all_env(f2);
	if(setenv(str2, val, 0)) {
		errno = 1;
		perror("Couldn't add to variable2");
	}
	print_all_env(f3);
	if(setenv(str1, val1, 0)) {
		errno = 1;
		perror("Couldn't change to variable1");
	}
	print_all_env(f4);
	if(setenv(str1, val1, 1)) {
		errno = 1;
		perror("Couldn't change to variable1");
	}
	print_all_env(f5);
	return 0;
}
