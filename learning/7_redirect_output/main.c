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

        if ((fd = open("file2.txt", O_WRONLY | O_CREAT, 0777)) == -1) // creates a file and specifies its permissions in octal and not decimal
        {
            printf("Could not open the file.\n");
            return (2);
        }
        dup2(fd, STDOUT_FILENO); //changes the stdout fd to the file fd
        close(fd); //closes the fd, as it'll not be used anymore
        execlp("cat", "cat", "filee1.txt", NULL); //now, instead of printing to terminal (fd == 1), it'll be printed to the file, as during this process the stdout was changed to the file
    }
    else if (pid > 0)
    {
        int waitstatus;

		wait(&waitstatus);
		printf("%d wait status\n", waitstatus);
        printf("%d parent\n", STDOUT_FILENO);
        execlp("cat", "cat", "file2.txt", NULL);
    }
	printf("Never gets here\n");
    return (0);
}
