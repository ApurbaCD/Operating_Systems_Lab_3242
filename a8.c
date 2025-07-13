
/*
Write a C program to show how two related processes can communicate with
each other by an unnamed pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];             // pipefd[0] = read end, pipefd[1] = write end
    pid_t pid;
    char buffer[100];

    // Create unnamed pipe
    if (pipe(pipefd)==-1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Create child process
    pid=fork();

    if (pid<0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    else if (pid==0) {
        // --- Child Process ---
        close(pipefd[0]); // Close unused own read end

        char *msg="Hello from child process!\n";
        write(pipefd[1],msg,strlen(msg)); // Send message to parent

        close(pipefd[1]); // Close write end after writing
        exit(0);
    }

    else {
        // --- Parent Process ---
        close(pipefd[1]); // Close unused own write end

        read(pipefd[0],buffer,sizeof(buffer)); // Read message from child
        printf("Parent received: %s",buffer);

        close(pipefd[0]); // Close read end
        wait(NULL);       // Wait for child to terminate
    }

    return 0;
}

