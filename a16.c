/*
Write a C program to handle racing situations in a multi-threaded process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global counter shared between threads
int counter = 0;

// Mutex to protect counter
pthread_mutex_t lock;

// Thread function to increment the counter
void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);    // Begin critical section
        counter++;                    // Shared resource
        pthread_mutex_unlock(&lock);  // End critical section
    }
    return NULL;
}

// Thread function to decrement the counter
void* decrement(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        counter--;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    // Create threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, decrement, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Print result
    printf("Final counter value: %d\n", counter);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

