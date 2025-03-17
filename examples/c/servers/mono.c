/* CpS 250 Server Example - Single Tasking 
 * 
 * Toy server (reads integer from stdin, prints range of integers from 0 to value-read to stdout)
 * that cannot handle multiple concurrent "requests" but which does allow graceful shutdown with
 * SIGTERM and SIGINT (^C) .
 * 
 * by Jordan Jueckstock
 * (c) 2024, Bob Jones University
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t should_quit = 0;

void quit_handler(int sig) {
	(void)sig;
	should_quit = 1;
}

int main() {
	int ret = 1;
	struct sigaction sa = { .sa_handler = quit_handler };

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	while (!should_quit) {
		int n;
		printf("[%d] enter request: ", getpid()); fflush(stdout);
		if (scanf("%d", &n) == 1) {
			for (int i = 0; i < n; ++i) {
				printf("[%d] request(%d) -> %d\n", getpid(), n, i);
				sleep(1);
			}
		}
		if (feof(stdin) || ferror(stdin)) {
			perror("scanf");
			goto cleanup;
		}
	}
	ret = 0;
cleanup:
	printf("\n[%d] QUIT (%s)\n", getpid(), ret == 0 ? "OK" : "EOF/error");
	return ret;
}
