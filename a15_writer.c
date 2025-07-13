/*
Write a C program to show how data inconsistency arises in two unrelated
processes when they share a memory space.
*/


// writer.c or increment process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65); // Generate a unique key
    int shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT); // Create or get shared memory

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    int *data = (int*) shmat(shmid, NULL, 0); // Attach to shared memory
    if (data == (void*) -1) {
        perror("shmat");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        int temp = *data;      // Read
        usleep(100000);        // Simulate delay
        temp += 1;             // Modify
        *data = temp;          // Write back
        printf("Writer: %d\n", *data);
    }

    shmdt(data); // Detach
    return 0;
}

