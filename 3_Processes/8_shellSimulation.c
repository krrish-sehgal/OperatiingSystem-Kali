#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_LINE 80

int main(){
    char*args[(MAX_LINE/2)+1];
    while(true){
        printf("saySon > ");
        fflush(stdout); // to flush the output stream , any data in the buffer will be written to the terminal

        char input[MAX_LINE];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets");
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        //tokenize the args
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }    
        //if input is exit or null break and continue repectively
        if (args[0] == NULL) {
            continue;
        }
        if (strcmp(args[0],"exit\0")==0) {
            break;
        }
        printf(args[0]);
        pid_t pid;

        pid = fork();

        if(pid==0){
            //child process
            execvp(args[0],args);
        }else if(pid >0){
            //parent process
            wait(NULL);
        }else{
            perror("fork");
            return 1;
        }
    }
  return 0;
}