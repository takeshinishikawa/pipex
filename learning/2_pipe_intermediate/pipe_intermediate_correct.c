#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(void)
{
    int p1[2];
    int p2[2];

    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        printf("Could not create the pipe.\n");
        return (1);
    }
    int pid;

    pid = fork();
    if (pid == -1)
    {
        printf("Could not create the child process.\n");
        return (2);
    }
    if (pid == 0) //child process
    {
        close(p1[0]);
        close(p2[1]);
        int x;

        if (read(p2[0], &x, sizeof(x)) == -1)
        {
            printf("Could not read 'x'.\n");
            return (3);
        }
        printf("Received x %d.\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1)
        {
            printf("Could not write to 'x'.\n");
            return (4);
        }
        printf("Wrote x %d.\n", x);
        close(p1[1]);
        close(p2[0]);
    }
    else
    {
        close(p1[1]);
        close(p2[0]);

        int y;

        srand(time(NULL));
        y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1)
        {
            printf("Could not write to 'y'.\n");
            return (5);
        }
        printf("Wrote y %d.\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1)
        {
            printf("Could not read 'y'.\n");
            return (6);
        }
        printf("Result is %d.\n", y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    return (0);
}
