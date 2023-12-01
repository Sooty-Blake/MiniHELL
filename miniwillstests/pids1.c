#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*
int main(void)
{
	pid_t pid;

	printf("Fork here.\n");
	pid = fork();
	if (pid == -1)
	{
		return (1); //error
	}
	printf("\nfork successful!\n");
	if (pid == 0)
	{
		//fork return value is 0, making this the chld process
		printf("Child: my internal pid is %d.\n", pid);
	}
	else if (pid > 0)
	{
		printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
	}
	return (0);
}
*/



/*
void	child_routine(pid_t pid, int *nb)
{
	printf("Child: Hi! me child. PID received from fork = %d\n", pid);
	printf("Child: The number is %d\n", *nb);
}

void	parent_routine(pid_t pid, int *nb)
{
	printf("Parent: I'm the parent. PID received from fork = %d\n", pid);
	printf("Parent: The number is %d\n", *nb);
	*nb *= 2;
	printf("Parent: The modified number is %d\n", *nb);
}

int main()
{
	pid_t pid;
	int nb;

	nb = 42;
	printf("Before fork, the number is %d\n", nb);
	pid = fork();
	if (pid == -1)
	{
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		child_routine(pid, &nb);
	}
	else if (pid > 0)
	{
		parent_routine(pid, &nb);
	}
	return (EXIT_SUCCESS);
}
*/

/*
int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Child: Me child. internal pid is %d.\n", pid);
		sleep(1);
		printf("Child: Done!\n");
	}
	else if (pid > 0)
	{
		printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
		printf("Parent: Done!\n");
	}
	return (0);
}
*/

/*
int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        printf("Child: I'm the child, my internal pid is %d.\n", pid);
        printf("Child: Done!\n");
    }
    else if (pid > 0)
    {
        printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
        while (1) // Infinite loop, the parent will never end !
            usleep(1);
    }
    return (0);
}
*/

// Define a macro for a specific child exit code (if we do not
// specify this exit code during compilation with the 
// -D CHILD_EXIT_CODE=[number] option), by default, it will be 42:
#ifndef CHILD_EXIT_CODE
# define CHILD_EXIT_CODE 42
#endif

// Define a macro for the expected exit status
#define EXPECTED_CODE 42

// Child process routine:
void	child_routine(pid_t pid)
{
	printf("\e[36mChild: Hi! I'm the child. PID received from fork = %d\e[0m\n",
			pid);
	printf("\e[36mChild: Exiting with exit code %d.\e[0m\n",
			CHILD_EXIT_CODE);
	exit(CHILD_EXIT_CODE);
}

// Parent process routine:
void	parent_routine(pid_t pid)
{
	int	status;

	printf("Parent: I'm the parent. PID received from fork = %d\n", pid);
	printf("Parent: Waiting for my child with PID [%d].\n", pid);
	waitpid(pid, &status, 0); // Wait for child
	printf("Parent: My child exited with status %d\n", status);
	if (WIFEXITED(status)) // If child exited normally
	{
		printf("Parent: My child's exit code is %d\n",
				WEXITSTATUS(status));
		if (WEXITSTATUS(status) == EXPECTED_CODE)
			printf("Parent: That's the code I expected!\n");
		else
			printf("Parent: I was not expecting that code...\n");
	}
}

int	main(void)
{
	pid_t	pid; // Store fork's return value

	pid = fork(); // Create child process
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0) // Child process
		child_routine(pid);
	else if (pid > 0) // Parent process
		parent_routine(pid);
	return (EXIT_SUCCESS);
}
