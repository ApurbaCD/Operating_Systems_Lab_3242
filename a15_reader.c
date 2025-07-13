/*
Write a C program to show how data inconsistency arises in two unrelated
processes when they share a memory space.
*/


// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65); // Same key
    int shmid = shmget(key, sizeof(int), 0666); // Access existing shared memory

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    int *data = (int*) shmat(shmid, NULL, 0);
    if (data == (void*) -1) {
        perror("shmat");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        int temp = *data;
        usleep(100000);
        temp += 2;
        *data = temp;
        printf("Reader: %d\n", *data);
    }

    shmdt(data);
    return 0;
}

