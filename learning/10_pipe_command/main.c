#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Create a pipe to communicate between two processes
 * 
 * 1) Create a child process and change the std output
 * sending through a pipe the content read by cat
 * 2) Create another child process and reads from std input
 * its content and execute grep to find the line that has the
 * argv informed by the user
 */

int main (int argc, char **argv)
{
    printf("%d\n", argc);
    printf("%s\n", argv[1]);
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        printf("Could not create pipe.\n");
        return (1);
    }
    int pid1;
    pid1 = fork();
    if (pid1 < 0)
    {
        printf("Could not fork.\n");
        return (2);
    }
    if (pid1 == 0)
    {
        //child will cat from txt file0
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("cat", "cat", "file.txt", NULL);
    }
    //parent process
    int pid2;

    pid2 = fork();
    if (pid2 < 0)
    {
        printf("Could not fork.\n");
        return (3);
    }
    if (pid2 == 0) //child process will grep "bat" from stdin
    {    
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("grep", "grep", argv[1], NULL);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
