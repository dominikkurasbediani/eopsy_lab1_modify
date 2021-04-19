#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILD 5
#define WITH_SIGNALS

#ifdef WITH_SIGNALS // handling keyboardInterrupt and the print handler that prints message of the termination of the process
	int interrupt_pressed = 0; // not bool because C does not support bools without stdbool.h

	void keyboardInterrupt() // keyboard interrupt handler
	{
		interrupt_pressed = 1; // the global mark
		printf("\n\tparent[%d]:\t\t Keyboard interrupt received.\n", getpid());
	}

	void printHandler()
	{
		printf("\nchild[%d]: Termination.", getpid());
	}
#endif

int main()
{
	pid_t child_pid = 1; // child's pid
	pid_t parent_pid = 1; // parent's pid
	int count = 0; // counter


	printf("parent[%d]:\n", getpid());
	for(int i = 0; i < NUM_CHILD; i++)
	{
		#ifdef WITH_SIGNALS // focing ignoring off all the signals
			for(int i = 0; i < NSIG; i++) // NSIG = total number of signals
				sigignore(i); // implementation in signals.h 
			signal(SIGCHLD, SIG_DFL);
			signal(SIGINT, keyboardInterrupt);
		#endif

		if(!(child_pid = fork())) // child_pid == 0, so child
		{
			#ifdef WITH_SIGNALS // using the print handler 
				signal(SIGINT, printHandler);
				signal(SIGINT, SIG_DFL);
			#endif

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

		#ifdef WITH_SIGNALS // killing the processes
			if(interrupt_pressed)
			{
				printf("\n\tparent[%d]: \t\tChild creation interrupted.\n", getpid());
				kill(-2, SIGTERM); // -2 < -1 so SIGTERM is sent to all the process group
				break;
			}
		#endif
	}

	while(1)
	{
		pid_t s;
		pid_t w = wait(&s);
		if(w == -1)
		{
			break;
		}
		else
		{
			printf("\nchild[%d]:\t\t process terminated.\n", w);
			count++;
		}
	}

	printf("\n\n\n%d processes were terminated\n", count);

	#ifdef WITH_SIGNALS // restoring default signals
		for(int i = 0; i < NSIG; i++)
			signal(i, SIG_DFL);
	#endif

    return 0;
}

