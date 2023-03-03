// icat: interruptable cat
// Systems programming demo that shows the effect of signals on pending system calls (depending on compilation flags)
// (c) 2016-2023, Bob Jones University
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <signal.h>
#include <unistd.h>
#include <errno.h>

volatile bool should_quit = false;

void handler(int sig) {
    // Warning: this may not be safe!  See signal(7) for details...
    printf("Got signal %d\n", sig);

    if (sig == SIGTERM) {
        should_quit = true;
    }
}

int main() {
    char *buf = NULL;
    size_t size = 0;

    struct sigaction sa_int = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigaction(SIGINT, &sa_int, NULL);
    sa_int.sa_flags = 0; // no SA_RESTART
    sigaction(SIGTERM, &sa_int, NULL);

    bool tryAgain = true;
    while (tryAgain && !should_quit) {
        printf("Reading from stdin: ");
        if (getline(&buf, &size, stdin) == -1) {
            if (ferror(stdin)) {
                if (errno == EINTR) {
                    // This case occurs only for SIGTERM because SA_RESTART is NOT specified 
                    printf("getline() was interrupted by a signal.\n");
                    clearerr(stdin); // must clear the error flag
                } else {
                    perror("I/O error occurred");
                    tryAgain = false;
                }
            } else {
                // EOF
                tryAgain = false;
            }
        } else {
            if (buf[strlen(buf)-1] == '\n') {
                buf[strlen(buf)-1] = '\0';
            }
            printf("\nRead %zd bytes: '%s'.\n", strlen(buf), buf);
        }
    }

    return 0;
}

