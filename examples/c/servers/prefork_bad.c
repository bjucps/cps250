#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_WORKERS 20

static volatile sig_atomic_t should_quit = 0;
static volatile sig_atomic_t reaped_kids = 0;

static int g_workers = 1, g_current = 0;

void quit_handler(int sig) {
	should_quit = 1;
}

void child_handler(int sig) {
	pid_t who;
	while ((who = waitpid(-1, NULL, WNOHANG)) > 0) {
		++reaped_kids;
	}
}

void server_loop() {
	printf("[%d] worker entering server_loop\n", getpid());
	for (;;) {
		int n;
		printf("[%d] enter request: ", getpid()); fflush(stdout);
		if (scanf("%d", &n) == 1) {
			for (int i = 0; i < n; ++i) {
				printf("[%d] request(%d) -> %d\n", getpid(), n, i);
				sleep(1);
			}
		} else if (errno != EINTR) {
			printf("[%d] worker error (%s)\n", getpid(), strerror(errno));
			exit(1);
		}
	}
}

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("usage: %s NUM_WORKERS\n", argv[0]);
		return 1;
	}
	g_workers = atoi(argv[1]);
	if ((g_workers <= 0) || (g_workers > MAX_WORKERS)) {
		printf("bogus worker count %d\n", g_workers);
		return 1;
	}

	struct sigaction sa = { .sa_handler = quit_handler };
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	
	sa.sa_handler = child_handler;
	sigaction(SIGCHLD, &sa, NULL);

	while (!should_quit) {
		while (reaped_kids > 0) {
			printf("[%d] server reaped kid\n", getpid());
			--reaped_kids;
			--g_current;
		}
		while (g_current < g_workers) {
			pid_t kid = fork();
			if (kid > 0) {
				++g_current;
				printf("[%d] server preforked worker pid %d (%d active)\n", getpid(), kid, g_current);
			} else if (kid == 0) {
				server_loop();
				// never returns!
			} else {
				perror("fork");
				return 1;
			}
		}
	}
	printf("\n[%d] QUIT\n", getpid());
	return 0;
}
