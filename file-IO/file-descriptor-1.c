#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main() {

    int fd1, fd2;
    fd1 = open("foo1.txt", O_RDONLY, 0);
    //close(fd1);
    fd2 = open("foo1.txt", O_RDONLY, 0);
    printf("fd1 = %d\n", fd1);
    printf("fd1-1 = %d\n", fd2);
    exit(0);
}
