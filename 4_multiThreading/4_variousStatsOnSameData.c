#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <string.h> // Added for strcmp

// Global variables for results
int avg_result = 0;
int min_result = 0;
int max_result = 0;
int arr_size;
int *arr;

// Function prototypes
void compute_avg(int* arr, int size);
void compute_max(int* arr, int size);
void compute_min(int* arr, int size);
void* runner(void* arg);

int main(int argc, char *argv[]) {
    pthread_t threads[3];
    pthread_attr_t attr[3]; // Array of thread attributes

    // Check if there are enough arguments
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

     arr_size = argc - 1;
    arr = malloc(sizeof(int) * arr_size);

    // Parse command-line arguments into array
    for (int i = 0; i < arr_size; i++) {
        arr[i] = atoi(argv[i + 1]);
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Initialize thread attributes
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);
    pthread_attr_init(&attr[2]);

    // Create threads for average, max, and min computations
    pthread_create(&threads[0], &attr[0], runner, "avg");
    pthread_create(&threads[1], &attr[1], runner, "max");
    pthread_create(&threads[2], &attr[2], runner, "min");

    // Join threads to wait for completion
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Output results
    printf("Average: %d\n", avg_result);
    printf("Max: %d\n", max_result);
    printf("Min: %d\n", min_result);

    // Clean up
    free(arr);
    pthread_attr_destroy(&attr[0]);
    pthread_attr_destroy(&attr[1]);
    pthread_attr_destroy(&attr[2]);

    return 0;
}

void* runner(void* arg) {
    char* x = (char*)arg;

    if (strcmp(x, "avg") == 0) {
        compute_avg(arr, arr_size);
    } else if (strcmp(x, "max") == 0) {
        compute_max(arr, arr_size);
    } else if (strcmp(x, "min") == 0) {
        compute_min(arr, arr_size);
    } else {
        printf("Unknown task: %s\n", x);
    }

    return NULL;
}

void compute_avg(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    avg_result = sum / size;
}

void compute_max(int* arr, int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    max_result = max_val;
}

void compute_min(int* arr, int size) {
    int min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    min_result = min_val;
}
