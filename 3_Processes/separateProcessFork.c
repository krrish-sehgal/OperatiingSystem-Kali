#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

// Creatung a separate process using the UNIX fork() system call.

int main(){
    pid_t pid;
    //fork a child process
    pid = fork();

    if(pid < 0){
        fprintf(stderr,"Fork Failed");
        return 1;
    }else if(pid==0){
        //The child process which copied this program on address space will get the pid variable as 0 
        execlp("/bin/ls","ls",NULL);
        // /bin/ls specifies the "ls" command location and since no other directory route is provided to ls , it executes ls in the current directory as the child process will initally run in the parent's directory.
    }else{
        //parent process fork() call will return the actual process id of the child process to the pid var
        wait(NULL); // wait will wait for the program to finish , instead of NULL we can pass on the status variable
        printf("Child Complete");
    }
    return 0 ;
}
