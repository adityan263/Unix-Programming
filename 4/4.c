#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <limits.h>

#define N 10

int main() {

	int f_game, f_player, i;
	struct stat buff1, buff2;

	if(getuid() == geteuid()) {
		printf("compile file as superuser or any user other than current user \nset set-uid bit of executable as 1 and then execute\n");
		exit(0);
	}
	umask(0);
	f_game = open("owner_file", O_WRONLY | O_CREAT, 0644);
	if (f_game == -1) {
		printf("Could not open game_logs\n");
		return errno;
	}

	f_player = open("player_file", O_WRONLY | O_CREAT, 0644);
	if (f_player == -1) {
		printf("Could not open player_logs\n");
		return errno;
	}

	printf("uid: %d\teuid: %d\n", getuid(), geteuid());

	stat("player_file", &buff1);
	stat("owner_file", &buff2);

	printf("player_file owner u:%d\t g:%d\n", buff1.st_uid, buff1.st_gid);
	printf("owner_file owner  u:%d\t g:%d\n\n", buff2.st_uid, buff2.st_gid);

	chown("player_file", getuid(), getgid());

	stat("player_file", &buff1);
	stat("owner_file", &buff2);

	printf("player_file owner u:%d\t g:%d\n", buff1.st_uid, buff1.st_gid);
	printf("owner_file owner  u:%d\t g:%d\n\n", buff2.st_uid, buff2.st_gid);

	char t = '0';

	close(f_game);
	close(f_player);

	//reopen files to make sure previous ownership does not continue
	f_game = open("owner_file", O_WRONLY | O_APPEND);
	if (f_game == -1) {
		perror("owner_file");
		return errno;
	}
	f_player = open("player_file", O_WRONLY | O_APPEND);
	if (f_player == -1) {
		perror("player_logs");
		return errno;
	}

	for(i = 0; i < N; i++) {
		if (setreuid(geteuid(), getuid()) == -1) {
			perror("");
			return errno;
		}
		printf("Currently uid: %d\teuid: %d and writing player_file\n", getuid(), geteuid());

		if (write(f_player, &t, 1) != 1) {
			perror("player_logs");
			return errno;
		}

		if (setreuid(geteuid(), getuid()) == -1) {
			perror("");
			return errno;
		}
		printf("Currently uid: %d\teuid: %d    and writing owner_file\n", getuid(), geteuid());

		if (write(f_game, &t, 1) != 1) {
			perror("owner_file");
			return errno;
		}

		t++;
	}

	close(f_game);
	close(f_player);
	return 0;
}
