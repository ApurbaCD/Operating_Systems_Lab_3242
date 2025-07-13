/*
Write a C program to create a main process named ‘parent_process’ having 3
child processes without any grandchildren processes. Child Processes’
names are child_1, child_2, child_3. Trace the position in the process tree.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // Set the name of the parent process
    prctl(PR_SET_NAME, "parent_process", 0, 0, 0);

    pid_t pid;
    char *child_names[3] = {"child_1", "child_2", "child_3"};

    printf("Parent Process (PID: %d, PPID: %d) started.\n", getpid(), getppid());

    for (int i = 0; i < 3; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            // In child
            prctl(PR_SET_NAME, child_names[i], 0, 0, 0);
            printf("Child Process %s (PID: %d, PPID: %d)\n", child_names[i], getpid(), getppid());
            sleep(20);  // Stay alive for observation
            exit(0);
        }
        // Parent continues to next child
    }

    // Parent waits for children to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}


//WE can see the process tree by using 
//    pstree
//see in clear in gnome-terminal--bash--

//precise comman:
//pstree -p pid_parent

//or
// ps aux|grep executable_file_name(such as orphan_process)
