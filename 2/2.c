#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define MAX 256

int main(int argc, char* argv[]) {
	char *pwd, *dir, *temp, *final, buf[50];
	struct stat f;

	pwd = (char*)malloc(MAX);
	temp = (char*)malloc(MAX);
	final = (char*)malloc(MAX);
	
	getcwd(pwd, 50);
	
	if(argc > 1) {
		strcat(pwd, "/");
		strcat(pwd, argv[1]);
	}
	
	dir = strtok(pwd, "/");
	
	while(dir != NULL) {
		strcat(temp, "/");
		strcat(temp, dir);
		lstat(temp, &f);
		if(S_ISLNK(f.st_mode)) {
			readlink(temp, &buf[0], 50);
			strcat(final, "/");
			strcat(final, buf);
			strcpy(temp, final);
		}
		else {
			strcpy(final, temp);
		}
		dir = strtok(NULL, "/");
	}
	printf("%s\n", final);
	
	char dot='.', slash = '/', tilda = '~';
	int d = 0, j, i = 0;
	
	while(i + d < strlen(final)+1) {
		if(final[i+d] == dot && final[i+d+1] == dot) {
			j = i-2;
			while(final[j] != slash) j--;
			d += i - j + 2;
			i = j;
		}
	
		if(final[i+d] == dot && final[i+d+1] == slash)
			d+=2;
		
		if(final[i+d] == tilda) {
			d = i;
			i = 0;
		}
		
		if(final[i+d] == slash && final[i+d+1] == slash) {
			d = i + 1;
			i = 0;
		}
		
		final[i] = final[i+d];
		i++;
	}
	printf("%s\n", final);

	free(pwd);
	free(temp);
	free(final);
	return 0;
}
