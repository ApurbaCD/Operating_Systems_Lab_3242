//Write a C program to create an orphan process.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
	pid_t pid=fork();
	
	if(pid<0){
	    perror("fork failed ");
	    exit(EXIT_FAILURE);
	}
	
	else if(pid>0){
	    printf("This is the parent process with PID: %d and now parent is exiting ..\n",getpid());
	    exit(0);	
	}
	
	else{
            sleep(5);// Wait to ensure parent exits first
	    printf("This is the orphan process with pid: %d and parent process PID is %d",getpid(),getppid());
	    exit(0);	
	}
	return 0;

}
