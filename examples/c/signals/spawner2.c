// spawner2
// Systems programming demo that shows primitive IPC via multiple signals
// (c) 2016, Bob Jones University

//
// Build: gcc -std=gnu99 spawner.c -ospawner
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


// Variables manipulated by signal handlers need to be declared "volatile"
volatile bool g_quit = false;
volatile int g_num_kids = 0;

int g_delay = 1, g_status = 0;

// WARNING: printf() and other stdio functions inside signal
// handlers are NOT guaranteed to be safe/work/etc.  I use
// them here for demonstration purposes, but notice that I
// had to add calls to fflush() to make sure it behaved
// correctly.  In REAL code, just set flags/etc. inside your
// signal handlers...
void handler(int sig) {
    int who, status;

    switch (sig) {
        case SIGTERM:
            printf("[%d] SIGTERM received; shutting down...\n", getpid());
            fflush(stdout);
            g_quit = true;
            break;
        case SIGCHLD:
            printf("[%d] Got SIGCHLD; reaping zombie child...", getpid());
            fflush(stdout);

            while ((who = waitpid(-1, &status, WNOHANG)) > 0) {
                printf("%d with status %d\n", who, WEXITSTATUS(status));
                fflush(stdout);
                --g_num_kids;
            }
            break;
         case SIGUSR1:
            printf("[%d] Got SIGUSR1; spinning off child process...", getpid());
            fflush(stdout);
            who = fork();
            if (who < 0) {
                perror("fork");
            } else if (who == 0) {
                // CHILD
                sleep(g_delay);
                exit(g_status);
            } else {
                // PARENT
                printf("%d launched (delay=%d, status=%d)\n", who, g_delay, g_status);
                fflush(stdout);
                ++g_num_kids;
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

    // Allow user customization of delay/exit status of child process
    if (argc > 1) {
        g_delay = atoi(argv[1]);
    }
    if (argc > 2) {
        g_status = atoi(argv[2]);
    }

    printf("Spawner2 started (pid=%d)\n", getpid());

    // All our handling will be done by this sigaction(2) handler 
    struct sigaction sa = {
        .sa_handler = handler,
        // No other settings required for basic registration
    };
   
    // Register SIGTERM, SIGCHLD, and SIGUSR1 
    if (sigaction(SIGTERM, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }
    if (sigaction(SIGCHLD, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }
    if (sigaction(SIGUSR1, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }

    // Wait forever (until SIGTERM received)
    while (!g_quit) { pause(); }

    ret = 0;
cleanup:
    while (g_num_kids > 0) {
        pause();
    }
    return ret;
}

