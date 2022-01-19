#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <errno.h>

int main(int argc, char* argv[]) {
	int pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0) {
		int err = execlp("cat", "cat", "infile", NULL);
		if (err == -1) {
			perror("Error");
			return (errno);
		}
	} else {
		int wstatus;
		wait(&wstatus); //wait will return the child's process exit code
		if (WIFEXITED(wstatus)) //validates if the exit code is different from 0
		{
			int statusCode = WEXITSTATUS(wstatus);//this macro will get the error type
			if (statusCode == 0) {
				printf("Success\n");
			} else {
				printf("Failure with status code %d\n", statusCode);
			}
		}
	}
	return 0;
}
