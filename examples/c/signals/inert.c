// inert
// Systems programming demo that shows how non-responsive a Unix process can be if it ignores ALL ignorable signals
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Ignoring all signals...\n");

    int i;
    for (i = 1; i < 32; ++i) {
        if (signal(i, SIG_IGN) == SIG_ERR) {
            fprintf(stderr, "signal(%d, SIG_IGN) -> ", i);
            perror(NULL);
            // but keep going!
        }
    }

    printf("Now, try to kill me if you can!\n");

    pause();

    return 0;
}

