// pipe1
// Demonstration of writing into/reading out of a pipe (single process)
// (c) 2016-2023, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

int main() {
    int pipe_fds[2] = { -1, -1 };

    if (pipe(pipe_fds)) {
        perror("pipe");
        exit(1);
    }

    int readfd = pipe_fds[0];
    int writefd = pipe_fds[1];

    char *msg = "Hello, world!";

    printf("Writing '%s' to pipe...\n", msg);
    write(writefd, msg, strlen(msg));

    printf("Reading 256 bytes from pipe...\n");
    char buff[256];
    ssize_t recd = read(readfd, buff, sizeof(buff) - 1);
    if (recd < 0) {
        perror("read");
        exit(1);
    }
    buff[recd] = '\0';
    printf("\tGot '%s'\n", buff);
    
    close(pipe_fds[0]);
    close(pipe_fds[1]); 
    return 0;
}

