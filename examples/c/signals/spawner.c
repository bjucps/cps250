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

#include "safe_snprintf.h"

volatile sig_atomic_t g_num_kids = 0;


static char safe_printf_buff[256];
#define SAFE_PUTS(msg) write(1, msg, strlen(msg))
#define SAFE_PRINTF(fmt, ...) do {\
		safe_snprintf(safe_printf_buff, sizeof safe_printf_buff, fmt, __VA_ARGS__); \
		write(1, safe_printf_buff, strlen(safe_printf_buff)); \
	} while(0)

void handler(int sig) {
    int who, status;

	SAFE_PRINTF("handler: got signal %d...\n", sig);
    switch (sig) {
        case SIGCHLD:
            // If we have multiple children dying close together,
            // their SIGCHLDs may be merged/coalesced (i.e., we
            // may get only *one* SIGCHLD but need to reap *two*
            // zombies).  Therefore, in a SIGCHLD handler,
            // always *loop* using the non-blocking form of waitpid(2)...
            while ((who = waitpid(-1, &status, WNOHANG)) > 0) {
				SAFE_PRINTF("who=%d, status=%d\n", who, status);
                --g_num_kids;

                // Inject artificial delay to demonstrate
                // SIGCHLD signal coalescing/merging
                struct timespec delay = { .tv_nsec = 1000 };
                nanosleep(&delay, NULL);
            }
            break;
        default:
			// some other signal we don't care about
            break;
    }
}

int main(int argc, char **argv) {
    int ret = 1;
    int delay = 1, status = 0;
	sigset_t mask, oldmask;

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
	// create a signal-mask-set with only SIGCHLD selected
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);

	// BLOCK SIGCHLD (so it cannot interrupt us)
	// [old mask with SIGCHLD not blocked -> oldmask]
	sigprocmask(SIG_BLOCK, &mask, &oldmask);

	// check the count (no race condition with SIGCHLD)
    while (g_num_kids > 0) {
		// need to wait for SIGCHLD event[s]
		// (un-block and wait for the signals in oldmask, including SIGCHLD)
		// (will re-block as we return from sigsuspend)
		sigsuspend(&oldmask);
    }

	// UNBLOCK SIGCHLD finally (no need to capture old-mask)
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

    return ret;
}

