#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#define MAX (1800)

int main () { 
	FILE *ps_pipe, *grep_pipe; 
	int bytes_read, nbytes = 100; 
	char my_string[MAX]; 
	ps_pipe = popen ("ls -l", "r"); 
	grep_pipe = popen ("wc -l", "w");
	bytes_read = fread(my_string, MAX, 1, ps_pipe);
	printf("Output of ls -l | wc -l:\t");
	fflush(stdout);				    //else printf will print after output of command
	fprintf(grep_pipe, "%s", my_string);
	pclose (grep_pipe);
	return 0;
}
