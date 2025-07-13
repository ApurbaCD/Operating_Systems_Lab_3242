/*
Write a C program to create a main process named ‘parent_process’ having 3 10
child processes without any grandchildren processes.
Trace parent and child processes in the process tree.
Show that child processes are doing addition, subtraction and multiplication
on two variables initialized in the parent_process
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	int n=3;
	int a=4,b=5;
	//pid_t pid;
	printf("The parent process PID is: %d and parent's process parent PID is %d\n",getpid(),getppid());
	for(int i=0;i<n;i++){
	    pid_t pid=fork();
	    if(pid==0){
	    	printf("The process PID is: %d and parent PID is %d\n",getpid(),getppid());
		switch(i){
			case1:
			    printf("The addition of a,b is %d\n",a+b);
			    break;
			case2:
			    printf("The subtraction of a,b is %d\n",a-b);
			    break;
			case3:
			    printf("The multiplication of a,b is %d\n",a*b);
			    break;
		}
		exit(0);
	    }
	    
	    
			
	}
	//for(int i=0;i<1000000000;i++){}
	//for(int i=0;i<1000000000;i++){}
	//for(int i=0;i<1000000000;i++){}
	//or
	sleep(5);
	
	//In the mean time check process tree in terminal using this command
	//pstree 
	//Or more precisely by 
	// pstree -p parentpid(like 176278)
	
	wait(NULL);
	wait(NULL);
	wait(NULL);
	
	return 0;
		
	
}

//pstree
