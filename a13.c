/*
Write a C program to show how data inconsistency arises in a multi-threaded
process.
*/

#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++;  // Not atomic!
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        counter--;  // Not atomic!
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, decrement, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Expected counter = 0, but likely not zero due to race condition
    printf("Final counter value: %d\n", counter);

    return 0;
}

