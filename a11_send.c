
/*
Write a C program to show how two unrelated processes can communicate
with each other by a message queue.
*/


//sender

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    message.msg_type = 1;  // Message type > 0
    printf("Enter message to send: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);

    // Remove trailing newline
    size_t len = strlen(message.msg_text);
    if (len > 0 && message.msg_text[len - 1] == '\n') {
        message.msg_text[len - 1] = '\0';
    }

    // Send the message
    if (msgsnd(msqid, &message, strlen(message.msg_text) + 1, 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message sent successfully.\n");
    return 0;
}

