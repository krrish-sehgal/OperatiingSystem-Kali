#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

// Creating a separate process using the UNIX fork() system call.

int main(){
    char write_mssg[BUFFER_SIZE] = "Greetings";
    char read_mssg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;


    //create the pipe
    if(pipe(fd) == -1){
        fprintf(stderr, "Pipe failed");
    }
    //fork a child process

    pid = fork();
    if(pid< 0){
        fprintf(stderr, "fork failed");
        return 1;
    }else if(pid==0){
        printf("Control in the child proces\n");
        //child process
        //close the unused end of the pipe as you dont want the child(reciever to write into the half duplex pipe)
        close(fd[WRITE_END]);

        //read from the pipe 
        read(fd[READ_END],read_mssg,BUFFER_SIZE);
        printf("read %s",read_mssg);

        //close the write end of the pipe
        close(fd[READ_END]);
    }
    else if(pid >0){
        //parent process 
        //close the unused end of the pipe
        printf("Control in the parent process\n");
        close (fd[READ_END]);

        //write to the pipe
        write(fd[WRITE_END],write_mssg,strlen(write_mssg)+1);

        ///close the write end of the pupe
        close (fd[WRITE_END]);
    }
    //since here wait is not called , after termination child process will be stored as an orphan in the init process and will be removed when the init process calls the wait() system call ,to remove such orphans
    return 0 ;
}
