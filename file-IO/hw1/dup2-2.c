#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp) {

    int fd1, fd2;
    int dummy;
    char *newargv[2];

    fd1 = open( argv[1], O_RDONLY);

    dup2(fd1, 0);
    close(fd1);

    fd2 = open( argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);

    dup2(fd2, 1);
    close(fd2);

    newargv[0] = "cat";
    newargv[1] = (char *) 0;

    execve("/bin/cat", newargv, envp);

    exit(0);
}

