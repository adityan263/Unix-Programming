#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {
	int fr = open("file1", O_RDONLY);
	int fw = open("file2", O_WRONLY | O_CREAT, 0777);
	close(0);
	close(1);
	dup2(fr, 0);
	dup2(fw, 1);
	char str[20];
	scanf("%s", str);
	printf("%s\n", str);
	return 0;
}

