// spawner2
// Systems programming demo that shows primitive IPC via multiple signals
// (c) 2016-2023, Bob Jones University

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "safe_snprintf.h"

static char safe_printf_buff[256];
#define SAFE_PUTS(msg) write(1, msg, strlen(msg))
#define SAFE_PRINTF(fmt, ...) do {\
		safe_snprintf(safe_printf_buff, sizeof safe_printf_buff, fmt, __VA_ARGS__); \
		write(1, safe_printf_buff, strlen(safe_printf_buff)); \
	} while(0)


// Variables manipulated by signal handlers need to be declared "volatile"
volatile sig_atomic_t g_quit = false;
volatile sig_atomic_t g_num_kids = 0;
volatile sig_atomic_t g_to_spawn = 0;

int g_delay = 1, g_status = 0;

void handler(int sig) {
    int who, status;

    switch (sig) {
        case SIGTERM:
            SAFE_PRINTF("[%d] SIGTERM received; shutting down...\n", getpid());
            g_quit = true;
            break;
        case SIGCHLD:
            SAFE_PRINTF("[%d] Got SIGCHLD; reaping zombie child...\n", getpid());

            while ((who = waitpid(-1, &status, WNOHANG)) > 0) {
                SAFE_PRINTF("%d with status %d\n", who, WEXITSTATUS(status));
                --g_num_kids;
            }
            break;
         case SIGUSR1:
            SAFE_PRINTF("[%d] Got SIGUSR1; now have %d procs to spawn...\n", getpid(), ++g_to_spawn);
			break;
      default:
            SAFE_PRINTF("[%d] Unexpected signal caught %d!\n", getpid(), sig);
            break;
    }
}

int main(int argc, char **argv) {
    int ret = 1;
	sigset_t mask, oldmask;

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

	sigemptyset(&mask);
   
    // Register SIGTERM, SIGCHLD, and SIGUSR1 
    if (sigaction(SIGTERM, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }
	sigaddset(&mask, SIGTERM);
    if (sigaction(SIGCHLD, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }
	sigaddset(&mask, SIGCHLD);
    if (sigaction(SIGUSR1, &sa, NULL)) {
        perror("sigaction");
        goto cleanup;
    }
	sigaddset(&mask, SIGUSR1);

	sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (!g_quit) { 
		sigsuspend(&oldmask);
		while (g_to_spawn > 0) {
            pid_t who = fork();
            if (who < 0) {
                perror("fork");
            } else if (who == 0) {
                // CHILD
				sigprocmask(SIG_UNBLOCK, &mask, NULL);
                sleep(g_delay);
                exit(g_status);
            } else {
                // PARENT
                printf("%d launched (delay=%d, status=%d)\n", who, g_delay, g_status);
                fflush(stdout);
				--g_to_spawn;
                ++g_num_kids;
            }
		}
	}
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

    ret = 0;
cleanup:
	sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (g_num_kids > 0) {
		sigsuspend(&oldmask);
    }
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
    return ret;
}

