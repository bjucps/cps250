// icat: interruptable cat
// Systems programming demo that shows the effect of signals on pending system calls (depending on compilation flags)
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>

volatile bool should_quit = false;

void handler(int sig) {
    // Warning: this may not be safe!  See signal(7) for details...
    printf("Got signal %d\n", sig);

    if (sig == SIGTERM) {
        should_quit = true;
    }

    // Compatibility hack
    // If in "BSD" mode (the gnu99 default), we don't have to reestablish the signal handler
    // If in "System V" mode (the c99 default), we must reestablish the signal handler
#ifndef _BSD_SOURCE
    signal(sig, handler);
#endif
}

int main() {
    printf("Process %d...\n", getpid());

    signal(SIGINT, handler);
    signal(SIGTERM, handler);


    char buff[120];
    while (!should_quit) {
        fputs("[reading from STDIN...", stderr);
        fflush(stderr);
        ssize_t recd = read(STDIN_FILENO, buff, sizeof(buff));
        fputs("]\n", stderr);

        if (recd < 0) {
            perror("read");
            // Keep chugging...
        } else if (recd == 0) {
            // EOF
            fputs("[EOF]\n", stderr);
            break;
        } else {
            if (write(STDOUT_FILENO, buff, recd) < recd) {
                perror("write");
                break;
            }
        }
    }

    return 0;
}

