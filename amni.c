#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    char *fifo_path = "myfifo";  // Name of FIFO
    pid_t pid;
    char buffer[100];

    // Create FIFO (only if it doesn't exist)
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo (might already exist)");
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        // --- Child Process: Read from FIFO ---
        int fd = open(fifo_path, O_RDONLY);
        if (fd == -1) {
            perror("Child: open");
            exit(1);
        }

        read(fd, buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd);
        exit(0);
    }

    else {
        // --- Parent Process: Write to FIFO ---
        int fd = open(fifo_path, O_WRONLY);
        if (fd == -1) {
            perror("Parent: open");
            exit(1);
        }

        char message[] = "Hello from parent!";
        write(fd, message, strlen(message));
        close(fd);

        wait(NULL);  // Wait for child to finish
    }

    // Optionally delete the FIFO after use
    unlink(fifo_path);

    return 0;
}
