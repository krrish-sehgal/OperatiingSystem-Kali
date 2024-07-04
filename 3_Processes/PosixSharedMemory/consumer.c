#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    // size in bytes of shared memory object
    const int SIZE = 4096; 
    // name of the shared memory object
    const char *name = "OS";

    //Shared memory file descriptor 
    int shm_fd;
    //pointer to shared memory object
    void *ptr ;

    //open the shared memory object
    shm_fd = shm_open(name , O_RDONLY ,  0666);
    //first param = name of shared memory object
    //second param = shared memory obj is to be created if it does not yet exsist
    //last param specifes diretory permission

    // a successfull call to shm_open returns an integer file descritor for the shared memory obj

    //memory map the shared memory object
    ptr = mmap(0,SIZE, PROT_READ , MAP_SHARED, shm_fd , 0);
    //mmap established a memory mapped file containing the shared memory obj
    // returns a pointer to memory mapped file which will used for accessing the obj

    //read from the shared memory obj
    printf("%s", (char*)ptr);
    
    //remove the shared memory object
    shm_unlink(name);

    return 0;
}
