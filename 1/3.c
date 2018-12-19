#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main() {
	char buf[5];
	int f = open("f1", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(f == -1) {
		perror("cannot open file");
		return errno;
	}
	if (write(f, "abcde", 5) != 5) {
		fprintf(stderr, "file f: write: %s\n", strerror(errno));
		return 1;
	}
	if (close(f) == -1) {
		fprintf(stderr, "file f2: close: %s\n", strerror(errno));
		return 1;
	}

	f = open("f1", O_RDONLY | O_APPEND, S_IRUSR | S_IWUSR);
	if(f == -1) {
		perror("cannot open file");
		return errno;
	}
	if (lseek(f, 0, SEEK_SET) == -1) {
		fprintf(stderr, "file f3: lseek: %s\n", strerror(errno));
		return 1;
	}
	if (read(f, &buf, 5) != 5) {
		fprintf(stderr, "file f: write: %s\n", strerror(errno));
		return 1;
	}
	if (close(f) == -1) {
		fprintf(stderr, "file f2: close: %s\n", strerror(errno));
		return 1;
	}
	printf("%s\n",buf);

	return 0;
}
