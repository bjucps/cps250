// report
// Systems programming demo that prints out a notification of every signal reported
// (c) 2016, Bob Jones University
#define _BSD_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>

volatile bool should_quit = false;
volatile int signal_count[32];

void handler(int signal) {
    signal_count[signal] = 1;
    if (signal == SIGTERM) {
        should_quit = true;
    }
}

int main() {
    printf("Process %d installing signal handlers...\n", getpid());

    int i;
    for (i = 1; i < 32; ++i) {
        if (signal(i, handler) == SIG_ERR) {
            fprintf(stderr, "signal(%d, ...) -> ", i);
            perror(NULL);
        }
    }

    while (!should_quit) {
        pause();
        for (i = 1; i < 32; ++i) {
            if (signal_count[i]) {
                printf("Got signal %d [%s]\n", i, strsignal(i));
                signal_count[i] = 0;
            }
        }
    }

    return 0;
}
