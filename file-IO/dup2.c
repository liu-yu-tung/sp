#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    int fd;
    char *s;
    
    fd = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    dup2(fd, 1);

    close(fd);

    printf("Hello = %d\n", fd);

    exit(0);

}
