#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char* argv[])
{
	int arr[] = {1, 2, 3, 4, 1, 2, 7, 7, 7};
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
	int	id2;

	id = fork();
	id2 = fork();
	if (id == -1 || id2 == -1)
	{
		printf("fork() had an error.\n");
		return (1);
	}
	if (id == 0 && id2 == 0)
	{
		start = 0;
		end = arr_size / 3;
		printf("%i\n", id2);
	}
	else if (id == 0 && id2 != 0)
	{
		start = 1 * (arr_size / 3);
		end = 2 * (arr_size / 3);
		printf("%i\n", id2);
	}
	/*if (id == -1)
	{
		printf("fork() had an error.\n");
		return (1);
	}
	int id2;
	if (id == 0)
	{
		id2 = fork();
		if (id2 == -1)
		{
			printf("fork() had an error.\n");
			return (1);
		}
		else if (id == 0 && id2 == 0)
		{
			start = 0;
			end = arr_size / 3;
			printf("%i\n", id2);
		}
		else if (id == 0 && id2 != 0)
		{
			wait(NULL);
			start = 1 * (arr_size / 3);
			end = 2 * (arr_size / 3);
			printf("%i\n", id2);
		}
	}*/
	else
	{
		start = 2 * (arr_size / 3);
		end = arr_size;
		printf("%i\n", id);
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
	if ((id == 0 && id2 == 0))
	{
		close(pipedes[0]);
		write(pipedes[1], &sum, sizeof(sum));
		close(pipedes[1]);
		printf("Child2: %d\n", sum);
	}
	else if ((id2 != 0 && id == 0))
	{
		int	sumchild;
		wait(NULL);
/*wait() forces the parent process to wait for the child process execution.*/	
		close(pipedes[1]);
		read(pipedes[0], &sumchild, sizeof(sumchild));
		close(pipedes[0]);
		sum += sumchild;
		
		printf("Child1: %d\n", sum);
	}
	else if (id != 0 && id2 != 0)
	{
		wait(NULL);
		close(pipedes[1]);
		read(pipedes[0], &sum, sizeof(sum));
		close(pipedes[0]);
		sum += sum;
		
		printf("Parent: %d\n", sum);
	}
	return (0);
}