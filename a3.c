//Write a C program to create a zombie process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0); // Child exits — becomes zombie if parent doesn't wait
    }
    else {
        // Parent process
        printf("Parent process (PID: %d), child PID: %d\n", getpid(), pid);
        printf("Sleeping for 30 seconds so you can observe the zombie...\n");
        sleep(30); // During this time, child is a zombie
        printf("Now parent is exiting without calling wait().\n");
    }

    return 0;
}


//We can get this zombie process in terminal 

//     ps -ef | grep defunct

//This Displays all running processes in full format (all users, all details).

//     ps -el | grep Z

//ps -el: Shows processes in long format with all fields including status code (S, R, Z, etc.)

//     ps aux | grep Z

//ps aux: Shows all processes in detailed format, including processes run by all users.

//grep stands for Global Regular Expression Print.t is a command-line tool in Linux/UNIX used to search for a specific pattern of text in input.

//In Linux, a defunct process is a process that has terminated, but its parent has not yet read its exit status using wait() or waitpid().

//Such a process is also called a:

//    🧟 Zombie process
