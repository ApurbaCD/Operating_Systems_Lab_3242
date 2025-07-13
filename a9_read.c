/*
Write a C program to show how two unrelated processes can communicate
with each other by a named pipe.
*/

// reader
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    char *fifo = "myfifo";
    char buffer[100];

    // Open FIFO for reading
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Reader received: %s\n", buffer);
    close(fd);

    return 0;
}

