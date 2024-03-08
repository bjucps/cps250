// report
// Systems programming demo that prints out a notification of every signal reported
// (c) 2016-2023, Bob Jones University
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t should_quit = 0;
volatile sig_atomic_t signal_count[32];

void handler(int signal) {
    ++signal_count[signal];
    if (signal == SIGTERM) {
        should_quit = 1;
    }
}

int main() {
    printf("Process %d installing signal handlers...\n", getpid());

    int i;
	sigset_t mask, oldmask;
	sigemptyset(&mask);
    for (i = 1; i < 32; ++i) {
        if (signal(i, handler) == SIG_ERR) {
            fprintf(stderr, "signal(%d, ...) -> ", i);
            perror("signal");
        } else {
			sigaddset(&mask, i);
		}
    }

	sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (!should_quit) {
		sigsuspend(&oldmask);
        for (i = 1; i < 32; ++i) {
            if (signal_count[i]) {
                printf("Got signal %d [%s] %d time(s)\n", i, strsignal(i), signal_count[i]);
                signal_count[i] = 0;
            }
        }
    }
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

    return 0;
}
