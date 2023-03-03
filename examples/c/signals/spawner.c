// spawner
// Systems programming demo that shows a reasonably robust SIGCHLD handler implementation
// (c) 2016-2023, Bob Jones University

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile int g_num_kids = 0;

// WARNING: using printf() and other stdio functions inside signal handlers
// is technically undefined behavior.  Don't do it in real/non-demo code.
// (I.e., don't do it on assignments!)
void handler(int sig) {
    int who, status;

    switch (sig) {
        case SIGCHLD:
            printf("Got SIGCHLD; reaping zombie[s]...\n");    // Beware I/O in signal handlers!
            fflush(stdout);

            // If we have multiple children dying close together,
            // their SIGCHLDs may be merged/coalesced (i.e., we
            // may get only *one* SIGCHLD but need to reap *two*
            // zombies).  Therefore, in a SIGCHLD handler,
            // always *loop* using the non-blocking form of waitpid(2)...
            while ((who = waitpid(-1, &status, WNOHANG)) > 0) {
                printf("%d with status %d\n", who, WEXITSTATUS(status));
                fflush(stdout);
                --g_num_kids;

                // Inject artificial delay to demonstrate
                // SIGCHLD signal coalescing/merging
                struct timespec delay = { .tv_nsec = 1000 };
                nanosleep(&delay, NULL);
            }
            break;
        default:
            fprintf(stderr, "Unexpected signal caught %d [%s]\n", sig, strsignal(sig));
            fflush(stderr);
            break;
    }
}

int main(int argc, char **argv) {
    int ret = 1;
    int delay = 1, status = 0;

    // Allow user customization of delay/exit status of child process
    if (argc > 1) {
        delay = atoi(argv[1]);
    }
    if (argc > 2) {
        status = atoi(argv[2]);
    }

    // Register signal handler for SIGCHLD using sigaction(2)
    struct sigaction sa = {
        .sa_handler = handler,
        // No other settings required for basic registration
    };
    if (sigaction(SIGCHLD, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }

    // Fork off 10 child processes that will eventually raise SIGCHLD
    for (int i = 0; i < 10; ++i) {
        int kid = fork();
        if (kid < 0) {
            // ERROR BRANCH (still in PARENT)
            perror("fork");
            goto cleanup;
        } else if (kid == 0) {
            // CHILD BRANCH
            sleep(delay);
            exit(status);
        } else {
            // PARENT BRANCH
            printf("Child process %d spawned.\n", kid);
            ++g_num_kids;
        }
    }

    ret = 0;
cleanup:
    while (g_num_kids > 0) {
        pause();
    }
    return ret;
}

