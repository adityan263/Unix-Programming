#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <dirent.h>

void print_details(struct stat, struct passwd*, char*, int);
int print_file_type(struct stat *buff) {
	char *ptr;
	int ret = 0;

	if (S_ISREG(buff->st_mode))
		ptr = "Regular File";
	else if (S_ISDIR(buff->st_mode)) {
		ptr = "Directory";
		ret = 1;
	}
	else if (S_ISCHR(buff->st_mode))
		ptr = "Character special";
	else if (S_ISBLK(buff->st_mode))
		ptr = "Block mode";
	else if (S_ISFIFO(buff->st_mode))
		ptr = "FIFO File";
	else if (S_ISLNK(buff->st_mode))
		ptr = "Symbolic Link";
	else if (S_ISSOCK(buff->st_mode))
		ptr = "Socket";
	else
		ptr = "** Unkown mode **";

	printf("File Type\t:%s\n", ptr);
	return ret;
}

void print_directory_details(char* dir_name, int space) {
	DIR *dirp;
	char slash[] = "/";
	struct stat buff;
	struct passwd *pw;
	struct dirent *direntp;
	dirp = opendir(dir_name);
	if(stat(dir_name, &buff) == -1) {
		printf("Invalid directory name");
		exit(1);
	}
	if (!S_ISDIR(buff.st_mode)) {
		printf("Second argument is not a directory name");
		exit(1);
	}

	printf("Contents of directory %s:\n", dir_name);
	while ((direntp = readdir(dirp)) != NULL) {
		char *fname = direntp->d_name;
		char name[256];
		strcpy(name, dir_name);
		strncat(name, slash, 1);
		strcat(name, fname);
		if(stat(name, &buff) == -1) {
			exit(1);
		}
		pw = getpwuid(buff.st_uid);
		print_details(buff, pw, name, space);
	}
}

void print_details(struct stat buff, struct passwd *pw, char* fname, int space) {
	char prev[] = "..", cur[] = ".", sp[] = "   ";
	int i;
	i = 0;
	int l = strlen(fname);
	if((strcmp(fname, cur) != 0) && (strcmp(fname, prev) != 0)) {
		if(!(l > 2 && (fname[l-1] == '.' && ((fname[l-2] == '/') || (l > 3 && fname[l-2] == '.' && fname[l-3] =='/'))))) {
			while(i++ < space) printf("%s",sp);
			printf("Filename\t:%s\n", fname);
			i = 0;
			while(i++ < space) printf("%s",sp);
			printf("Username\t:%s\n", pw->pw_name);
			i = 0;
			while(i++ < space) printf("%s",sp);
			int ret = print_file_type(&buff);
			i = 0;
			while(i++ < space) printf("%s",sp);
			printf("Access Time\t:%s", ctime(&buff.st_atime));
			i = 0;
			while(i++ < space) printf("%s",sp);	
			printf("Mod Time\t:%s", ctime(&buff.st_mtime));
			i = 0;
			while(i++ < space) printf("%s",sp);	
			printf("Change Time\t:%s\n", ctime(&buff.st_ctime));
			if(ret)
				print_directory_details(fname, space+1);
		}
	}
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("Usage: ./a.out <file_name> <directory_name>");
		exit(1);
	}

	struct stat buff;
	if(stat(argv[1], &buff) == -1) {
		printf("Invalid filename");
	}
	else {
		struct passwd *pw;
		pw = getpwuid(buff.st_uid);
		print_details(buff, pw, argv[1], 0);
	}

	print_directory_details(argv[2], 0);

	return 0;
}
