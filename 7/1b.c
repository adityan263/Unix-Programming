#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void sigterm_handler(int signo) {
	printf("SIGTERM caught with signo = %d\n", signo);
}

int main() {
	struct sigaction action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_sigaction = NULL;

	action.sa_handler = sigterm_handler;
	sigaction(SIGTERM, &action, NULL);

	action.sa_handler = SIG_IGN;
	sigaction(SIGINT, &action, NULL);

	action.sa_handler = SIG_DFL;
	sigaction(SIGSEGV, &action, NULL);

	pause();
	return 0;
}
