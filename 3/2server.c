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
	if (argc < 2) {
		printf("Usage: ./a.out <filename>");
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	char buff[256];
	struct stat stat_buff;
	if(fd == -1) {
		printf("Can't open");
		return 1;
	}

	fstat(fd, &stat_buff);
	printf("server:Before reading\nAccess time: %sModification time: %sChange time: %s\n", ctime(&stat_buff.st_atime), ctime(&stat_buff.st_mtime), ctime(&stat_buff.st_ctime));
	
	sleep(5);
	
	if(read(fd, &buff, sizeof(buff)) <= 0) {
		printf("Error in reading from FIFO");
		return 2;
	}
	printf("Read from FIFO:%s\n", buff);
	fstat(fd, &stat_buff);
	
	printf("server:after reading\nAcess time: %sModification time: %sChange time: %s\n", ctime(&stat_buff.st_atime), ctime(&stat_buff.st_mtime), ctime(&stat_buff.st_ctime));
	return 0;
}
