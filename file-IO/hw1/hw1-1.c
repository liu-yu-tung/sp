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

    /**
     * chech if the arguments contain "-a" or "--append" 
     */

    for (int i=1; i<argc; i++) {
        if ((strcmp(argv[i], s0)) == 0 || strcmp(argv[i], s1) == 0) {
            append = true;
            append_pos = i;
        }
    }

    /**
     * allocate fds for each open files
     */

    int *fds = malloc((argc-1) * sizeof(int));

    /**
     * open each file based on the flag, 
     * and each file in the argument except append flag will only have one fd to access, 
     * but if any file appears multiple times it will have multiple fds.
     */

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

    /** read input from standard input, including pipes and keyboard. 
     * Then, for each fd, write the character according to their fd
     */
    
    while (read(0, read_buf, 1) != 0) {
        for (int i=1; i<argc; i++) {
            write(fds[i], read_buf, 1);
    }
        if (!append) {
            write(1, read_buf, 1);
        }
    }

    /**
     * close each fd
     */

    for (int i=0; i<argc-1; i++) {
        close(fds[i]);
    }

    exit(0);
}

