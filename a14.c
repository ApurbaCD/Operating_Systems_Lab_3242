/*
Write a C program to show how data inconsistency arises in two related
processes (e.g., parent & child processes) when they share a memory space.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    key_t key = 1234;
    int shmid;
    int *shared_counter;

    // Create shared memory segment for one int
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to shared memory
    shared_counter = (int *)shmat(shmid, NULL, 0);
    if (shared_counter == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    *shared_counter = 0;  // Initialize shared counter to zero

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {  // Child process
        for (int i = 0; i < 100000; i++) {
            (*shared_counter)++;  // Increment shared counter without synchronization
        }
        printf("Child done incrementing\n");
        // Detach and exit
        shmdt(shared_counter);
        exit(EXIT_SUCCESS);
    } 
    else {  // Parent process
        for (int i = 0; i < 100000; i++) {
            (*shared_counter)++;  // Increment shared counter without synchronization
        }
        wait(NULL);  // Wait for child to finish

        printf("Parent and child finished\n");
        printf("Final shared counter value: %d (Expected 200000)\n", *shared_counter);

        // Detach and remove shared memory
        shmdt(shared_counter);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

