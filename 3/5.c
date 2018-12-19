#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<inttypes.h>
#include<time.h>
#include<stdlib.h>

#define TO_MICRO(x) ((x)*1000000)
#define N 10

int main() {
	int i;
	struct timeval start;
	struct timeval end;
	double sum = 0;
	int f;

	for (i = 0; i < N; i++) {
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		double diff = TO_MICRO(end.tv_sec - start.tv_sec) +
			   (end.tv_usec - start.tv_usec);
		sum += diff;
	}

	double average = sum / N;
	printf("getpid() avg. time:\t%lf usec\n", average);
	sum = 0;
	for (i = 0; i < N; i++) {
		gettimeofday(&start, NULL);
		f = fork();
		gettimeofday(&end, NULL);
		double diff = TO_MICRO(end.tv_sec - start.tv_sec) +
			   (end.tv_usec - start.tv_usec);
		if (f) {
			/* parent */
			sum += diff;
		}
		else {
			/*child*/
			exit(0);
		}
	}
	average = sum / N;
	printf("fork() avg. time:\t%lf usec\n", average);
}
