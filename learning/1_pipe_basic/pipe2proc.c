#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char* argv[])
{
	int arr[] = {1, 2, 3, 4, 1, 2, 7, 7};
	int	arr_size;
	int	start;
	int	end;
	
/*each pipe need two communication points*/
	int pipedes[2];
/*pipe() function opens two fds one for writing "pipedes[1]" and another for reading "pipedes[0]".
**It's a good practice to check if pipe didn't get an error, the return of the fctn is "-1", if error.*/
	if (pipe(pipedes) == -1)
	{
		printf("pipe() had an error.\n");
		return (1);
	}
	arr_size = sizeof(arr) / sizeof(int);
/*fork() duplicate the calling process. The new process is called child and its id is always "0".
**while the calling process id is always differente from "0".
**If fork() fails it return "-1".*/
	int	id;

	id = fork();
	if (id == -1)
	{
		printf("fork() had an error.\n");
		return (1);
	}
	else if (id == 0)
	{
		start = 0;
		end = arr_size/2;
	}
	else
	{
		start = arr_size / 2;
		end = arr_size;
	}
	int	sum;
	int	i;

	sum = 0;
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	if (id == 0)
	{
		close(pipedes[0]);
		write(pipedes[1], &sum, sizeof(sum));
		close(pipedes[1]);
		printf("Child: %d\n", sum);
	}
	else
	{
		int	sumchild;

/*wait() forces the parent process to wait for the child process execution.*/	
		wait(NULL);
		close(pipedes[1]);
		read(pipedes[0], &sumchild, sizeof(sumchild));
		close(pipedes[0]);
		sum += sumchild;
		printf("Parent: %d\n", sum);
	}
	return (0);
}