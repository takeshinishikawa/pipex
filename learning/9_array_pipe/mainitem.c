#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/**
 * Communication between two processes
 * 1) Child process should generate an array of random numbers 
 * and send them to parent through a pipe.
 * 2) Parent should read the pipe and get the array of random
 * numbers and print them in the terminal.
 */

int number = 10;

int main(int argc, char *argv[])
{
    int pipefd[2];

    if(pipe(pipefd) == -1)
    {
        printf("Pipe could not be created.\n");
        return (1);
    }

    int pid;

    pid = fork();
    if (pid == -1)
    {
        printf("Fork could not generate the child process.\n");
        return (2);
    }
    if (pid == 0)
    {
        close(pipefd[0]);
        int y[number];
        int i;
        srand(time(NULL));
        i = 0;
        while (i < number)
        {
            y[i] = rand() % 10 + 1;
            printf("Random number %d is %d.\n", i, y[i]);
            if (write(pipefd[1], &y[i], sizeof(y[i])) < 0)
            {
                printf("Error in write().\n");
                return (2);
            }
            i++;
        }
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        int x[number];
        int i;
        int sum;
        srand(time(NULL));
        i = 0;
        sum = 0;
        while (i < number)
        {
            x[i] = rand() % 10;
            if(read(pipefd[0], &x[i], sizeof(x[i])) < 0>)
            {
                printf("Error in read().\n");
                return (3);
            }
            sum += x[i];
            i++;
        }
        printf("Sum of random numbers received is %d.\n", sum);
        wait(NULL);
        close(pipefd[0]);
    }
    return (0);
}