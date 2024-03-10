/* CpS 250 Server Example - Multi-Tasking [Pre-forking (correct)]
 * 
 * Variant of toy server that pre-forks a "pool" of N worker processes.
 * (N is a required CLI argument.)
 * Avoids the overhead of fork-per-request, and shuts down cleanly,
 * even waiting for outstanding requests to complete.
 * Uses a "process group" to allow the main process to broadcast-kill
 * all workers simultaneously with a SIGTERM on shutdown.
 * Then uses sigsuspend and a SIGCHLD handler to monitor the clean
 * shutdown of all workers before terminating itself.
 *
 * by Jordan Jueckstock
 * (c) 2024, Bob Jones University
 */
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
	(void)sig;
	should_quit = 1;
}

void child_handler(int sig) {
	(void)sig;
	pid_t who;
	while ((who = waitpid(-1, NULL, WNOHANG)) > 0) {
		++reaped_kids;
	}
}

void server_loop() {
	printf("[%d] worker (pgid=%d) entering server_loop\n", getpid(), getpgrp());
	while (!should_quit) {	// SIGTERM will make us break out of the loop here
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
	exit(0); // remove this to fork-bomb yourself (kind of funny to watch--once)
}

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	sigset_t mask, oldmask;

	if (argc < 2) {
		printf("usage: %s NUM_WORKERS\n", argv[0]);
		goto cleanup;
	}
	g_workers = atoi(argv[1]);
	if ((g_workers <= 0) || (g_workers > MAX_WORKERS)) {
		printf("bogus worker count %d\n", g_workers);
		goto cleanup;
	}

	struct sigaction sa = { .sa_handler = quit_handler };
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	
	sa.sa_handler = child_handler;
	sigaction(SIGCHLD, &sa, NULL);

	// make ourselves a "process group" leader
	if (setpgid(0, 0) < 0) {
		perror("setpgid");
		goto cleanup;
	}

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
				signal(SIGINT, SIG_IGN);	// ignore ^C in workers (only SIGTERM should kill them)
				server_loop();
				// never returns!
			} else {
				perror("fork");
				goto cleanup;
			}
		}
	}
	printf("\n[%d] QUIT\n", getpid());
	ret = EXIT_SUCCESS;
cleanup:
	if (g_current > 0) {
		// send SIGTERM to the entire process group (any living workers)
		kill(-getpid(), SIGTERM);

		// signal-safe-wait for all outstanding workers to die
		sigemptyset(&mask);
		sigaddset(&mask, SIGCHLD);
		sigprocmask(SIG_BLOCK, &mask, &oldmask);
		while (g_current > 0) {
			sigsuspend(&oldmask);
			printf("[%d] server reaped %d worker(s)\n", getpid(), reaped_kids);
			g_current -= reaped_kids;
		}
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
	}
	return ret;
}
