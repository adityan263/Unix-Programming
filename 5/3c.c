#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<sys/ipc.h>



int main(int argc, char *argv[]) {
	int fd;
	char *addr;
	struct stat sb;
	fd = shm_open("logs.txt", O_RDONLY, 0);
	fstat(fd, &sb);
	addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	printf("Read data:\n");
	printf("%s",addr);
}
