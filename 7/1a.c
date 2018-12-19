#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void sigterm_handler(int signo) {
	printf("SIGTERM caught with signo = %d\n", signo);
}

int main() {

	signal(SIGTERM, sigterm_handler);
	signal(SIGINT, SIG_IGN);
	signal(SIGSEGV, SIG_DFL);

	pause();
	return 0;
}
