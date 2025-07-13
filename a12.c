
/*
Write a C program to show how two related processes can communicate with
each other by a message queue.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msqid;
    struct msg_buffer msg;
    pid_t pid;
    int status;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'B');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create message queue or get if exists
    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {  // Child process - sender
        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello from child process!");

        if (msgsnd(msqid, &msg, strlen(msg.msg_text) + 1, 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        printf("Child: message sent\n");
        exit(EXIT_SUCCESS);
    }
    else {  // Parent process - receiver
        wait(&status);

        if (msgrcv(msqid, &msg, sizeof(msg.msg_text), 0, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Parent: received message: %s\n", msg.msg_text);

        // Optionally remove message queue after use
        msgctl(msqid, IPC_RMID, NULL);
    }

    return 0;
}

