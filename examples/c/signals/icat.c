// icat: interruptable cat
// Systems programming demo that shows the effect of signals on pending system calls 
// (c) 2016-2024, Bob Jones University
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t should_quit = 0;

void handler(int sig) {
    if (sig == SIGTERM) {
        should_quit = 1;
    }
}

int main() {
	int ret = EXIT_FAILURE;
    char buff[128];

	struct sigaction sa = {
		.sa_handler = handler
	};
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
    
	printf("Process %d...\n", getpid());
    while (!should_quit) {
        fputs("[reading from STDIN...", stderr);
        fflush(stderr);
        ssize_t recd = read(STDIN_FILENO, buff, sizeof(buff));
        fputs("]\n", stderr);

        if (recd < 0) {
			if (errno == EINTR) {
				perror("read interrupted by signal");
			} else {
				perror("read, other problem");
				goto cleanup;
			}
        } else if (recd == 0) {
            // EOF
            fputs("[EOF]\n", stderr);
			break;
        } else {
            if (write(STDOUT_FILENO, buff, recd) < recd) {
                perror("write");
				goto cleanup;
            }
        }
    }

	ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

