/*
Write a C program to create a main process named ‘parent_process’ having
‘n’ child processes without any grandchildren processes. Child Processes’
names are child_1, child_2, child_3,......., child_n. Trace the position in the
process tree. Number of child processes (n) and name of child processes will
be given in the CLI of Linux based systems.
Example:
$ ./parent_process 3 child_1 child_2 child_3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <child_1> <child_2> ... <child_n>\n", argv[0]);
        //printf("Usage: %s <n> <child_1> <child_2> ... <child_n>\n", argv[0]);
        exit(1);
    }
    // ./a 3 child_1 child_2 child_3 total 5 string. that means argc is 5 and nor argv[1]=3 
	
    int n = atoi(argv[1]);
    //printf("%d is the argc value \n",argc);
    if (argc != n + 2) {
        fprintf(stderr, "Error: Expected %d child names but got %d.\n", n, argc - 2);
        exit(1);
    }

    printf("Main process / parent_process started. PID = %d\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            printf("This is %s. PID: %d, PPID: %d\n", argv[i + 2], getpid(), getppid());
            exit(0); // Prevent grandchildren
        }
    }

    // Parent waits for all child processes
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent process PID: %d finished.\n", getpid());
    return 0;
}

//you can use prctl to rename parent process, child process
