#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include<setjmp.h>

static jmp_buf env;

static void sigint_handler(int sig) {
	long int i = 0;
	printf("interrupt between alarm() and pause()...\n");
	while(i++<1000000000);		    //wasting time
	printf("done\n");		    //this line should not print as alarm handler is called
}

static void sigalrm_handler(int sig) {
	printf("SIGALRM handler of new_sleep() function\n");
	longjmp(env, 1);
}

static void sigalrm_handler1(int sig) {
	printf("old SIGALRM handler called, old alarm not erased\n");
}

unsigned int new_sleep(unsigned int secs){

	unsigned int prev_alrm;
	void (*olddisposition)(int);
	sigset_t mask;
	printf("\n");

	if((olddisposition = signal(SIGALRM, sigalrm_handler)) == SIG_ERR)
		return(secs);
	if(setjmp(env) == 0){
		prev_alrm = alarm(secs);
		kill(0, SIGINT);	    //just to test race condition is handled
		pause();
	}

	if(signal(SIGALRM, olddisposition) == SIG_ERR)
		printf("Could not reset old disposition\n");

	sigprocmask(0, NULL, &mask);
	if(sigismember(&mask, SIGALRM)) {
		printf("SIGALRM was masked by signal(), mask removed\n");
		sigemptyset(&mask);
		sigaddset(&mask, SIGALRM);
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
	}

	printf("\n");

	return(alarm(prev_alrm));
}

int main(){

	unsigned int unslept;

	if(signal(SIGALRM, sigalrm_handler1) == SIG_ERR)
		printf("Could not set SIGALRM disposition in main\n");
	if(signal(SIGINT, sigint_handler) == SIG_ERR)
		printf("Could not set SIGINT disposition in main\n");
	alarm(3);
	printf("alarm(3)\nnew_sleep(1)\n");

	unslept = new_sleep(1);
	printf("new_sleep returned: %u sec unslept\n", unslept);

	pause();
	return 0;
}

