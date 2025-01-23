#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 100

int get_random();
int allocate_map(void);
int allocate_pid();
void release_pid(int pid);

bool* pid_map;
pthread_mutex_t pid_mutex = PTHREAD_MUTEX_INITIALIZER;

int allocate_map(void) {
    pid_map = malloc(sizeof(bool) * (MAX_PID - MIN_PID + 1));
    if (pid_map == NULL) {
        return -1; // Failure
    }
    for (int i = 0; i <= MAX_PID - MIN_PID; i++) {
        pid_map[i] = false;
    }
    return 1; // Success
}

int get_random() {
    return rand() % (MAX_PID - MIN_PID + 1);
}

int allocate_pid() {
    // mutex, short for "mutual exclusion," is a synchronization primitive used to prevent multiple threads from simultaneously accessing and modifying shared resources, which can lead to race conditions and data corruption. In essence, a mutex allows only one thread to execute a critical section of code at a time.
    pthread_mutex_lock(&pid_mutex);
    int pid;
    do {
        pid = get_random();
    } while (pid_map[pid]);
    pid_map[pid] = true;
    pthread_mutex_unlock(&pid_mutex);
    return pid + MIN_PID;
}

void release_pid(int pid) {
    pid -= MIN_PID;
    pthread_mutex_lock(&pid_mutex);
    if (pid_map[pid]) {
        pid_map[pid] = false;
        printf("Release pid %d\n", pid + MIN_PID);
    } else {
        printf("PID %d is not associated with any process\n", pid + MIN_PID);
    }
    pthread_mutex_unlock(&pid_mutex);
}

void* thread_function(void* arg) {
    int pid = allocate_pid();
    if (pid == -1) {
        printf("No PID available for thread %lu\n", pthread_self());
        return NULL;
    }
    
    printf("Thread %lu allocated PID %d\n", pthread_self(), pid);
    int sleep_time = rand() % 10 + 1; // Sleep for 1 to 10 seconds
    sleep(sleep_time);
    release_pid(pid);
    printf("Thread %lu released PID %d after sleeping for %d seconds\n", pthread_self(), pid, sleep_time);
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    pthread_t threads[NUM_THREADS];

    if (allocate_map() == -1) {
        fprintf(stderr, "Failed to initialize PID map\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        //the ampersand threads will the threadID allocated by the machine , we also have our own pid allocator working as well.
        // but the join listens to threadID to complete
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    free(pid_map); // Free the allocated memory for pid_map
    printf("All threads have completed.\n");
    return 0;
}
