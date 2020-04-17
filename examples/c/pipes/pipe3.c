// pipe3
// Demonstration of capturing a child process's STDOUT using a pipe
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int ret = 1;
    int pipe_fds[2] = { -1, -1 };
    int kid = 0;

    if (argc < 2) {
        printf("usage: %s PROG_TO_RUN [ARGS_TO_PROG...]\n", argv[0]);
        goto cleanup;
    }

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
        //----------------

        printf("[Child %d] Closing READ end of pipe...\n", getpid());
        if (close(pipe_fds[0])) {
            perror("close [child]");
            exit(1);
        }

        printf("[Child %d] Duplicating WRITE end of pipe to STDOUT...\n", getpid());
        if (dup2(pipe_fds[1], STDOUT_FILENO) < 0) {
            perror("dup2 [child]");
            exit(1);
        }

        printf("[Child %d] Closing extra handle to WRITE end of pipe...\n", getpid());
        if (close(pipe_fds[1])) {
            perror("close [child]");
            exit(1);
        }

        printf("[Child %d] Launching '%s'\n", getpid(), argv[1]);
        printf("------------------------------------------------------------\n");
        execvp(argv[1], &argv[1]);
        perror("execl [child]");
        exit(1);
    }

    // Parent-only branch
    //--------------------

    // TRY THIS: remove this close() call and see what happens! 
    printf("[Parent %d] Forked child process %d, closing WRITE end of pipe...\n", getpid(), kid);
    if (close(pipe_fds[1])) {
        perror("close");
        goto cleanup;
    }
    pipe_fds[1] = -1;   // Don't close it again (see cleanup code)

    printf("[Parent %d] Reading output from child process...\n", getpid());
    char buff[1024];
    ssize_t recd;
    while ((recd = read(pipe_fds[0], buff, sizeof(buff))) > 0) {
        buff[recd] = '\0';
        printf("[Parent %d] Received from child: %s", getpid(), buff);
    }
    printf("------------------------------------------------------------\n");
   
    ret = 0;
cleanup:
    if (pipe_fds[0] >= 0) { close(pipe_fds[0]); }
    if (pipe_fds[1] >= 0) { close(pipe_fds[1]); }
    if (kid) {
        int status;
        int who = wait(&status);
        printf("[Parent %d] Cleaned up child (%d) that exited with status %d\n",
                getpid(), who, WEXITSTATUS(status));
    }
    return ret;
}

