
/*
Write a C program to show how two unrelated processes can communicate
with each other by a named pipe.
*/


//mkfifo myfifo  (Use mkfifo() or the shell command)

// writer
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include<sys/stat.h>
#include<sys/types.h>
int main() {
    int fd;
    char *fifo = "myfifo";
    //mkfifo(fifo,0666);
    // Open FIFO for writing
    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("Open failed");
        exit(1);
    }

    char message[] = "Hello from Writer! ok ";
    write(fd, message, strlen(message));
    close(fd);

    return 0;
}

