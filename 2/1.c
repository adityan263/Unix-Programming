#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main() {
	char buf[7];
	if(mkdir("D1", 0700) == -1) {
		perror("D1: ");
		exit(errno);
	}

	if(open("D1/f1", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR) == -1) {
		perror("D1/f1: ");
		exit(errno);
	}

	if(write(f, "hello\n", 6) ) {
		perror("D1/f1: ");
		exit(errno);
	}
	
	if(mkdir("D2", 0707) == -1) {
		perror("D2:");
		exit(errno);
	}
	
	if(link("D1/f1", "D2/f2") == -1) {
		perror("D2/f2:");
		exit(errno);
	}
	
	if(chmod("D2/f2", S_IRUSR | S_IWUSR | S_IROTH | S_IXOTH) == -1) {
		perror("D2/f2: ");
		exit(errno);
	}
	
	close(f);
	return 0;
}
