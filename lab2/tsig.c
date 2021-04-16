#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILD 2
int main()
{
	pid_t child_pid = 1; // child's pid
	pid_t parent_pid = 1; // parent's pid
	int count = 0; // counter

	printf("parent[%d]:\n", getpid());
	for(int i = 0; i < NUM_CHILD; i++)
	{
		if(!(child_pid = fork())) // child_pid == 0, so child
		{
			printf("\n\tparent[%d]:\t\tcreated child[%d]\n", getppid(), getpid()); // printing ppid and pid of child
			sleep(10); // sleeping for 10s
			printf("\n\t\t\t\tchild[%d] completed execution.\n", getpid());
			exit(0);
		}
		else if(child_pid < 0) // negative means an fork() returned an error
		{
			printf("\n\tparent[%d]:\t\tfailed to create a child\n", getpid());
			kill(-1, SIGTERM); // terminating all the children. -1 means send SIGTERM to every process it has access to.
			exit(1);
		}
		sleep(1);
	}
    return 0;
}

