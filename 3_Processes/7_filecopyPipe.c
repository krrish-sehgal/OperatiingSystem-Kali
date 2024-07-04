#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#define size 50
#define READ_END 0
#define WRITE_END 1

int main(int arvuments, char* arv[]) 
{
    int fd[2];
    pid_t childid;
    char readBuff[size];
    pipe(fd);
    if( arvuments != 3 ) 
    {
        printf("ERROR: Need exactly 2 parameters.\n");
        exit(1);
    }
    int fileOpen = open(arv[1], 0);
    int TargetFile = open(arv[2], O_RDWR|O_CREAT|O_APPEND, 0666);

    if (fileOpen == -1 || TargetFile == -1){
        printf("File can not be opend\n");
        exit(1);
    }
    childid = fork();
    if (childid == 0) {
        close(fd[WRITE_END]);
        while (read(fd[READ_END], readBuff, sizeof(readBuff)) > 0) {
            write(TargetFile, readBuff, strlen(readBuff) - 1);
        }
        close(fd[READ_END]);
        close(TargetFile);
    }
    else{
        close(fd[READ_END]);
        while (read(fileOpen, readBuff, sizeof(readBuff)) > 0) {
            write(fd[WRITE_END], readBuff, sizeof(readBuff));
            memset(readBuff, 0, size);
        }
        close(fd[WRITE_END]);
        close(fileOpen);
        wait(NULL);
    }
}

