/*
Write a C program to show how two unrelated processes can communicate
with each other by a message queue.
*/

//receiver


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234

struct msg_buffer {
    //msg_type must be long
    long msg_type;
    char msg_text[100];
};

int main() {
    int msqid;
    struct msg_buffer message;

    // Get or create message queue
    msqid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Receive message of type 1
    if (msgrcv(msqid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s\n", message.msg_text);

    // Optionally remove the message queue after receiving
    // msgctl(msqid, IPC_RMID, NULL);

    return 0;
}

