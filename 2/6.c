#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main() {
	int pid = fork();
	if (!pid) {
		mode_t curr_mask;
		curr_mask = umask(0);
		printf("%o\n", curr_mask);
	}
	return 0;
}
