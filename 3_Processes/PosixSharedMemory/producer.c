#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//shm  => shared memory

int main(){
    // size in bytes of shared memory object
    const int SIZE = 4096; 
    // name of the shared memory object
    const char *name = "OS";
    //stirngs writtend to shared memory 
    const char *mssg_0 = "Hello";
    const char *mssg_1 = "World";

    //Shared memory file descriptor 
    int shm_fd;
    //pointer to shared memory object
    void *ptr ;

    // create the shared memory object using shm_open system call 
    shm_fd = shm_open(name , O_CREAT | O_RDWR, 0666);
    //first param = name of shared memory object
    //second param = shared memory obj is to be created if it does not yet exsist
    //last param specifes diretory permission

    // a successfull call to shm_open returns an integer file descritor for the shared memory obj
    
    //configuring the size of the shared memory object once the object is established
    ftruncate(shm_fd,SIZE);

    //memory map the shared memory object
    ptr = mmap(0,SIZE, PROT_WRITE , MAP_SHARED, shm_fd , 0);
    //mmap established a memory mapped file containing the shared memory obj
    // returns a pointer to memory mapped file which will used for accessing the obj
    // The map_shared flag signifies that the changes to the shared object will be visible to all theporcesses sharing the obejct
   
    //write thd sahred memory object
    sprintf(ptr, "%s", mssg_0);
    ptr += strlen(mssg_0);
    sprintf(ptr, "%s", mssg_1);
    ptr += strlen(mssg_1);


}
