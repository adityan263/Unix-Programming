#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
        if(argc != 2){
                printf("Usage: ./a.out <directory_name>");
                exit(1);
        }
        mkdir(argv[1], 777);
        chmod(argv[1], 01777);
}
