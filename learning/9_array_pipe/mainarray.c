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
            i++;
        }
        if (write(pipefd[1], &i, sizeof(i)) < 0) //it's very important to first, send the number of elements of the array
        {
            printf("Error in sending the number of elements in the array.\n");
            return (2);
        }
        if (write(pipefd[1], y, sizeof(y[i]) * i) < 0) //than it's possible to send the array indicating the number of elements
        {
            printf("Error in sending the array elements.\n");
            return (2);
        }
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        
        int i;

        if (read(pipefd[0], &i, sizeof(i)) < 0) //it's very important to first, get the number of elements of the array
        {
            printf("Could not read the number of elements.\n");
            return (3);
        }
        printf("Number of elements is %d\n", i);

        int x[i];
        int sum;
        int counter;

        sum = 0;
        counter = 0;
        if (read(pipefd[0], x, sizeof(x[i]) * i) < 0)
        {
            printf("Error in read().\n");
            return (4);
        }
        while (counter < i)
        {
            sum += x[counter];
            printf("Number is %d\n", x[counter]);
            counter++;
        }
        printf("Sum of random numbers received is %d.\n", sum);
        wait(NULL);
        close(pipefd[0]);
    }
    return (0);
}