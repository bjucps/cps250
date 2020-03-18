// pipe1
// Demonstration of writing into/reading out of a pipe (single process)
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <string.h>

#include <unistd.h>

int main() {
    int ret = 1;
    int pipe_fds[2] = { -1, -1 };

    if (pipe(pipe_fds)) {
        perror("pipe");
        goto cleanup;
    }

    char *msg = "Hello, world!";

    printf("Writing '%s' to pipe_fds[1]...\n", msg);
    if (write(pipe_fds[1], msg, strlen(msg)) < 0) {
        perror("write");
        goto cleanup;
    }

    printf("Reading 256 bytes from pipe_fds[0]...\n");
    char buff[256];
    ssize_t recd = read(pipe_fds[0], buff, sizeof(buff) - 1);
    if (recd < 0) {
        perror("read");
        goto cleanup;
    }
    buff[recd] = '\0';
    printf("\tGot '%s'\n", buff);
    
    ret = 0;
cleanup:
    if (pipe_fds[0] >= 0) { close(pipe_fds[0]); }
    if (pipe_fds[1] >= 0) { close(pipe_fds[1]); }
    return ret;
}

