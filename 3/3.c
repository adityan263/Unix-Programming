#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>

int b(jmp_buf jmpbuffer, int x) {
	printf("Value passed to b() is %d\n", x);
	longjmp(jmpbuffer, x);
}

int a(jmp_buf jmpbuffer) {
	printf("Entered a()\n");
	int x = setjmp(jmpbuffer);
	printf("In a() value of x is %d\n", x);
	return x;
}

int main() {
	jmp_buf jmpbuffer;
	int ret = a(jmpbuffer);
	if(ret != 0)
		exit(1);
	else
		printf("a() returned %d\n\n", ret);
	b(jmpbuffer, 0);
	printf("\n");
	b(jmpbuffer, 4);

	return 0;
}
