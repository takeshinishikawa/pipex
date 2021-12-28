#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

/**
 * @Create a fifo_file, write 5 random number on it, and reading the sum of them passed by another program. 
 */

int main(int argc, char *argv[])
{ 
    printf("Creating fifo file\n");
    /*fifo() have to parameters. The first is the name of the fifo file
    **and the second its permissions.*/
    if (mkfifo("sum", 0777) == -1)
    {
        /**
         * Check if a file with this name already existed.*/
        if (errno != EEXIST)
        {
            printf("fifo() could not create the file.\n");
            return (1);
        }
    }
    printf("Created fifo file\n");
    int fd;
    
    fd = open("sum", O_WRONLY);
    if (fd == -1)
    {
        printf("Failed to open sum file.\n");
        return (2);
    }

    int arr[6];
    int i;

    i = 0;
    srand(time(NULL));
    while (i < 5)
    {
        arr[i] = rand() % 100;
        if (write(fd, &arr[i], sizeof(arr[i])) == -1)
        {
            printf("Failed to write sum file.\n");
            return (3);
        }
        printf("wrote %d.\n", arr[i]);
        i++;
    }
    close(fd);
/**
 * Reads the total sum passed by another program through fifo file.**/
    fd = open("sum", O_RDONLY);
    if (read(fd, &arr[i], sizeof(arr[i])) == -1)
    {
        printf("Failed to read total sum in sum file.\n");
        return (3);
    }
    printf("Read total sum %d.\n", arr[i]);
    close(fd);
    return (0);
}
