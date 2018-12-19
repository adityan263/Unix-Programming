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
#include<string.h>
#include<error.h>
#include<errno.h>


int main(int argc, char *argv[]) {
	int fd; size_t len; char *addr;
	if((fd = shm_open("logs.txt", O_RDWR | O_CREAT, 0666)) == -1) {
		printf("shm_open failed\n");
		exit(1);
	}
	char *a = "Log\n";
	len = strlen(a); 
	ftruncate(fd, len*3);
	addr=mmap(NULL, len*3, PROT_WRITE, MAP_SHARED, fd, 0);
	if(*addr == -1) {
		printf("mmap failed %d\n",errno);
		exit(1);
	}
	close(fd);
	printf("writing data:\n");
	memcpy(addr+len*0, a, len);
	printf("%s",a);
	memcpy(addr+len*1, a, len);
	printf("%s",a);
	memcpy(addr+len*2, a, len);
	printf("%s",a);
	return 0;
}
