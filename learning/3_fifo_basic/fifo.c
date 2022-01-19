#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    printf("Creating fifo file\n");
    /*fifo() have to parameters. The first is the name of the fifo file
    **and the second its permissions.*/
    if (mkfifo("fifo_file", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("fifo() could not create the file.\n");
            return (1);
        }
    }
    printf("Created fifo file\n");
    int fd;

    printf("Opening\n");
    /*fifo() execution depends on writing and reading to be opened at the same time
    **if its not done, the program will wait until the one that is not in execution
    **to be executed.*/
    fd = open("fifo_file", O_RDWR);
    printf("Opened\n");
    /*it's a good practice to have the open() call
    **checked, when called.*/
    if (fd == -1)
    {
        printf("open() could not open the file.\n");
        return (2);
    }

    int x;

    x = 'A';

    if (write(fd, &x, sizeof(x)) == -1)
    {
        printf("write() could not write in the file.\n");
        return (3);
    }
    printf("Wrote the char  \"%c\" into fifo_file\n", x);
    char *buffer;

    if (read(fd, buffer, sizeof(buffer)) == -1)
    {
        printf("read() could not read the file.\n");
        return (3);
    }
    printf("Read into buffer the char \"%s\" from fifo_file\n", buffer);
    printf("Closing fifo_file\n");
    close(fd);
    printf("Closed\n");
    return (0);
}
