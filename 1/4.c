#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	char buf[10];
	int fd = open("f2", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

	if (fd == -1) {
		perror("cannot open f2");
		return errno;
	}

	if (lseek(fd, 10, SEEK_SET) == -1) {
		fprintf(stderr, "file f2: lseek: %s\n", strerror(errno));
		return 1;
	}
	if (write(fd, "0123456789", 10) != 10) {
		fprintf(stderr, "file f2: write: %s\n", strerror(errno));
		return 1;
	}	
	if (lseek(fd, 30, SEEK_SET) == -1) {
		fprintf(stderr, "file f2: lseek: %s\n", strerror(errno));
		return 1;
	}
	if (write(fd, "abcdefghij", 10) != 10) {
		fprintf(stderr, "file f2: write: %s\n", strerror(errno));
		return 1;
	}
	if (close(fd) == -1) {
		fprintf(stderr, "file f2: close: %s\n", strerror(errno));
		return 1;
	}

	system("od f2");
	printf("\n");

	fd = open("f2", O_RDONLY);
	if (fd == -1) {
		perror("cannot open f2");
		return errno;
	}

	int fd2 = open("f3", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd2 == -1) {
		perror("cannot open f3");
		return errno;
	}

	while(read(fd, buf, 1) != 0) {
		if(buf[0] != '\0')
			write(fd2, buf, 1);
	}

	if (close(fd) == -1) {
		fprintf(stderr, "file f2: close: %s\n", strerror(errno));
		return 1;
	}
	if (close(fd2) == -1) {
		fprintf(stderr, "file f3: close: %s\n", strerror(errno));
		return 1;
	}
	system("od f3");
}
