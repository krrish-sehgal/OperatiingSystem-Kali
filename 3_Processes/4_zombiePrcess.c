#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid;

    //fork a child process
    pid = fork();

    if(pid < 0){
        fprintf(stderr,"Fork Failed");
        return 1;
    }else if(pid==0){
        printf("Child Complete " );
        exit(0);
    }else{
        sleep(20);
        wait(NULL);

    }
    return 0 ;
    //run with ./a.out & , ampersand runs the process in background while you can use the same terminal and run ps -l to a see a process with state(under S header ) as Z (zombie)
}
