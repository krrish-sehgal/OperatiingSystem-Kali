#include <stdio.h>
#include <pthread.h>

//global data is shared among the threads
int sum; 
void*runner(void*param);

int main(int argc,char*argv[]){
  pthread_t tid;   //thread identifier
  pthread_attr_t attr; // set the attributes of the thread

    if(argc != 2){
        fprintf(stderr, "usage: a.out <interger value>\n");
        return -1;
    }

    if(atoi(argv[1]) < 0){
        fprintf(stderr, "%d must be >= 0\n",atoi(argv[1]));
        return -1;
    }

    //getting the default attributes
    pthread_attr_init(&attr);
    //create the thread
    pthread_create(&tid, &attr, runner , argv[1]);

    //wait for the thread to exit(synchonisation)
    pthread_join(tid,NULL);

    printf("sum = %d\n" , sum);

  return 0;
}

//thread begins control in this function
void*runner(void*param){
    int i , upper = atoi(param);
    sum = 0;

    for(i =1;i<=upper;i++){
        sum += i;
    }

    //thread gets done and is removed 
    pthread_exit(0);

}