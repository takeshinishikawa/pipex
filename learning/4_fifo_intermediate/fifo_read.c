#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/**
 * @Read a fifo_file, get 5 numbers from it, and write the sum of the fifo file to pass to the program.**/

int main(int argc, char *argv[])
{ 
    int fd = open("sum", O_RDONLY);
    if (fd == -1)
    {
        printf("Failed to open sum file.\n");
        return (1);
    }

    int arr[5];
    int i;
    int sum;

    i = 0;
    sum = 0;
    while (i < 5)
    {
        if (read(fd, &arr[i], sizeof(arr[i])) == -1)
        {
            printf("Failed to read sum file.\n");
            return (2);
        }
        printf("Received %d.\n", arr[i]);
        sum += arr[i];
        i++;
    }
    printf("Total sum is: %d.\n", sum);
    close(fd);

    fd = open("sum", O_WRONLY);
    if (write(fd, &sum, sizeof(sum)) == -1)
    {
        printf("Failed to write total sum in sum file.\n");
        return (3);
    }
    close(fd);
    return (0);
}