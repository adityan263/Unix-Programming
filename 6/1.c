#include <syslog.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	setlogmask (LOG_UPTO (LOG_NOTICE));

	openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	syslog (LOG_NOTICE, "Writing log1 AUP");
	syslog (LOG_INFO, "Writing log2 AUP");

	printf("cat /var/log/syslog | grep AUP\n");
	system("cat /var/log/syslog | grep AUP");

	closelog ();
}
