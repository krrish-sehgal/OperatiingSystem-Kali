#include<omp.h>
#include <stdio.h>
#define N 100

int main(int argc, char*argv[]){
    //sequential code

    //this will create a new thread, and run it in parallel 
    #pragma omp parallel
    {
        printf("I am a parallel region");
    }


    //this will create parallel threads and divide thw work in the for loop
    int c[N], a[N] = {1,2,12}, b[N] = {1,2,1};
    int i =0;
    #pragma omp parallel for
    {  
       for(i=0;i<3;i++){
        c[i] = a[i] + b[i];
        printf("%d ",c[i]);
       } 

    }
    return 0;
}
