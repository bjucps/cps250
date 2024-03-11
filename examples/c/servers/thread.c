/* CpS 250 Server Example - Multi-Tasking [Threading]
 * 
 * Variant of toy server that creates a new worker thread for each "request" received.
 * Handles concurrent requests and detaches each worker thread so it needs no join/cleanup.
 *
 * by Jordan Jueckstock
 * (c) 2024, Bob Jones University
 */
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t should_quit = 0;

void quit_handler(int sig) {
	(void)sig;
	should_quit = 1;
}

void * handle_request(void *arg1) {
	intptr_t n = (intptr_t)arg1;
	for (intptr_t i = 0; i < n; ++i) {
		printf("[%d:%d] request(%" PRIdPTR ") -> %" PRIdPTR "\n", getpid(), gettid(), n, i);
		sleep(1);
	}
	pthread_detach(pthread_self());
	return NULL;
}

int main() {

	struct sigaction sa = { .sa_handler = quit_handler };
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	while (!should_quit) {
		intptr_t n;
		printf("[%d:%d] enter request: ", getpid(), gettid()); fflush(stdout);
		if (scanf("%" PRIdPTR, &n) == 1) {
			pthread_t kid;
			if (pthread_create(&kid, NULL, handle_request, (void *)n)) {
				perror("pthread_create");
				return 1;
			}
		}
	}
	printf("\n[%d:%d] QUIT\n", getpid(), gettid());
	return 0;
}
