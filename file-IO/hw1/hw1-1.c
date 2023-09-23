#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {

    int fd;

    char read_buf[2];
    bool append = false;
    
    char s0[10];
    char s1[10];

    strcpy(s0, "-a");
    strcpy(s1, "--append");

    int append_pos = -1;

    for (int i=1; i<argc; i++) {
        if ((strcmp(argv[i], s0)) == 0 || strcmp(argv[i], s1) == 0) {
            append = true;
            append_pos = i;
        }
    }

    //printf("append = %d\n", append);
    int *fds = malloc((argc-1) * sizeof(int));

    for (int i=1; i<argc; i++) {
        if (i != append_pos) {
            if (append) {
                fds[i] = open(argv[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            }
            else {
                fds[i] = open(argv[i], O_WRONLY |  O_TRUNC | O_CREAT, 0644);
            }
        }
    }
    
    while (read(0, read_buf, 1) != 0) {
        for (int i=1; i<argc; i++) {
            write(fds[i], read_buf, 1);
    }
        if (!append) {
            write(1, read_buf, 1);
        }
    }

    for (int i=0; i<argc-1; i++) {
        close(fds[i]);
    }

    exit(0);
}

