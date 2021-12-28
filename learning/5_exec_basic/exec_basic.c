#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int pid;

    pid = fork();
    if (pid == -1)
    {
        printf("fork() had an error.\n");
        return (1);
    }
    if (pid == 0)
    {
        int fd;

        
        if ((fd = open("file2.txt", O_WRONLY | O_CREAT, 0777)) == -1)
        {
            printf("Could not open the file.\n");
            return (2);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execlp("cat", "cat", "file1.txt", NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
        execlp("cat", "cat", "file1.txt", NULL);
        
    }
    return (0);
}
