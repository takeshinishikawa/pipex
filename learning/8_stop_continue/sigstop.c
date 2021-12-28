#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler_sigtstp(int sig)
{
    printf("Stop not allowed.\n");
}


int main(int argc, char *argv[])
{
    struct sigaction sa;
    
    sa.sa_handler = &handler_sigtstp;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa, NULL);
    
    int x;
    printf("Input number: "); //press ctrl+z here (SAME AS SENDING SIGTSTP). When the process stops, you can type "fg" (SAME AS SENDING SIGCONT) and the process will be put back into foreground
    scanf("%d", &x);
    printf("Result %d * 5 is equal to %d\n.", x, x * 5);
    return (0);
}