/*
Write a C program to analyze the effect of local and global variables on a
parent process and a child process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var=100;  // Global variable

int main() {
    int local_var=50;  // Local variable

    pid_t pid=fork();  // Create child process

    if (pid<0) {
        perror("Fork failed");
        exit(1);
        //Use exit(1) only when the child fails or something goes wrong
        //exit(0) , It tells the operating system and the parent process that the child finished successfully.
    }
    else if(pid==0) {
        // Child process
        global_var+=10;
        local_var+=10;

        printf("Child Process:\n");
        printf("PID=%d,PPID=%d\n",getpid(),getppid());
        printf("Global variable=%d\n",global_var);
        printf("Local variable=%d\n",local_var);
    }
    else {
        // Parent process
        sleep(1);  // Ensure child runs first (for clarity)
        global_var-=5;
        local_var-=5;

        printf("\nParent Process:\n");
        printf("PID=%d\n",getpid());
        printf("Global variable=%d\n",global_var);
        printf("Local variable=%d\n",local_var);
    }

    return 0;
}

