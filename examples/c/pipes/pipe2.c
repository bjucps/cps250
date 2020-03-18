// pipe2
// Demonstration of passing data from parent process to child process using a pipe
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret = 1;
    int pipe_fds[2] = { -1, -1 };
    int kid = 0;

    printf("[%d] Creating pipe...\n", getpid());
    if (pipe(pipe_fds)) {
        perror("pipe");
        goto cleanup;
    }

    printf("[%d] Forking child process...\n", getpid());
    kid = fork();
    if (kid < 0) {
        perror("fork");
        goto cleanup;
    } else if (kid == 0) {
        // CHILD BRANCH
        printf("[%d] Closing WRITE end of pipe...\n", getpid());
        if (close(pipe_fds[1])) {
            perror("close [child]");
            exit(1);
        }

        printf("[%d] Reading 256 bytes from pipe_fds[0]...\n", getpid());
        char buff[256];
        ssize_t recd = read(pipe_fds[0], buff, sizeof(buff) - 1);
        if (recd < 0) {
            perror("read [child]");
            exit(1);
        }
        buff[recd] = '\0';
        printf("[%d]\t...got '%s'\n", getpid(), buff);

        printf("[%d] DONE\n", getpid());
        exit(0);    // STOP CHILD RIGHT HERE
    }

    // Parent-only branch
    printf("[%d] Forked child process %d, closing READ end of pipe...\n", getpid(), kid);
    if (close(pipe_fds[0])) {
        perror("close");
        goto cleanup;
    }
    pipe_fds[0] = -1;   // Don't close it again (see cleanup code)

    const char *msg = "Dear child, here is some input.  Love, parent...";
    printf("[%d] Writing '%s' to pipe_fds[1]...\n", getpid(), msg);
    if (write(pipe_fds[1], msg, strlen(msg)) < 0) {
        perror("write");
        goto cleanup;
    }

   
    ret = 0;
cleanup:
    if (kid > 0) {
        int status;
        int who = wait(&status);
        printf("[%d] Cleaned up child (%d) that exited with status %d\n",
                getpid(), who, WEXITSTATUS(status));
    }
    if (pipe_fds[0] >= 0) { close(pipe_fds[0]); }
    if (pipe_fds[1] >= 0) { close(pipe_fds[1]); }
    return ret;
}

