// pipe2
// Demonstration of passing data from parent process to child process using a pipe
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

void doChild(int readfd, int writefd) {
    printf("[Child %d] Closing WRITE end of pipe...\n", getpid());
    close(writefd);

    printf("[Child %d] Reading 256 bytes from pipe...\n", getpid());
    char buff[256];
    ssize_t recd = read(readfd, buff, sizeof(buff) - 1);
    if (recd < 0) {
        perror("read [child]");
        exit(1);
    }
    buff[recd] = '\0';
    printf("[Child %d]\t...got '%s'\n", getpid(), buff);

    printf("[Child %d] DONE\n", getpid());
    exit(0);    // STOP CHILD RIGHT HERE

}

int main() {
    int ret = 1;
    int pipe_fds[2] = { -1, -1 };
    int kid = 0;

    printf("[Parent %d] Creating pipe...\n", getpid());
    if (pipe(pipe_fds)) {
        perror("pipe");
        exit(1);
    }

    int readfd = pipe_fds[0];
    int writefd = pipe_fds[1];

    printf("[Parent %d] Forking child process...\n", getpid());
    kid = fork();
    if (kid < 0) {
        perror("fork");
        exit(1);
    } else if (kid == 0) {
        doChild(readfd, writefd);
    }

    // Parent executes this
    printf("[Parent %d] Forked child process %d, closing READ end of pipe...\n", getpid(), kid);
    close(readfd);

    const char *msg = "Dear child, here is some input.  Love, parent...";
    printf("[Parent %d] Writing '%s' to pipe...\n", getpid(), msg);
    write(writefd, msg, strlen(msg));

    return 0;
}

