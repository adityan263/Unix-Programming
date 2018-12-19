#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>

int main(int argc, char** argv) {
	int fd;
	if(mkfifo(argv[1], 0666)) {
		printf("Can't make FIFO");
		return 1;
	}

	char buff[] = "abcdefghi123456";
	struct stat stat_buff;
	fd = open(argv[1], O_WRONLY);
	if(fd == -1) {
		printf("Can't open");
		return 2;
	}
	fstat(fd, &stat_buff);
	
	printf("client:before writing\nAccess time: %sModification time: %sChange time: %s\n", ctime(&stat_buff.st_atime), ctime(&stat_buff.st_mtime), ctime(&stat_buff.st_ctime));
	
	if(write(fd,&buff,sizeof(buff)) <= 0) {
		printf("Error in writing to FIFO");
		return 2;
	}
	fstat(fd, &stat_buff);
	
	printf("client:after writing before reading\nAccess time: %sModification time: %sChange time: %s\n", ctime(&stat_buff.st_atime), ctime(&stat_buff.st_mtime), ctime(&stat_buff.st_ctime));

	sleep(4);
	return 0;
}	
