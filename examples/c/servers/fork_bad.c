#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t should_quit = 0;

void quit_handler(int sig) {
	should_quit = 1;
}

void handle_request(int n) {
	for (int i = 0; i < n; ++i) {
		printf("[%d] request(%d) -> %d\n", getpid(), n, i);
		sleep(1);
	}
}

int main() {

	struct sigaction sa = { .sa_handler = quit_handler };
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	while (!should_quit) {
		int n;
		printf("[%d] enter request: ", getpid()); fflush(stdout);
		if (scanf("%d", &n) == 1) {
			pid_t kid = fork();
			if (kid > 0) {
				printf("[%d] server forked kid %d\n", getpid(), kid);
				// no wait -- watch for zombies!
			} else if (kid == 0) {
				handle_request(n);
				exit(0);
			} else {
				perror("fork");
				return 1;
			}
		}
	}
	printf("\n[%d] QUIT\n", getpid());
	return 0;
}
