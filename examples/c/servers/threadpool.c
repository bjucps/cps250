/* CpS 250 Server Example - Multi-Tasking [Thread-Pool]
 * 
 * Variant of toy server that creates a pool of worker threads and feeds them via a queue.
 * Also tracks all created threads in a linked list and explicitly joins each on shutdown.
 * Uses CV to wait/notify worker threads about available work (broadcast to all on shutdown).
 *
 * by Jordan Jueckstock
 * (c) 2024, Bob Jones University
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "list.h"

#define MAX_WORKERS 20

static volatile sig_atomic_t should_quit = 0;

// type of items in work queue
typedef struct {
	int n;
	struct list_head entry;
} WorkItem;

// global work queue head (with lock/CV for sync/wait)
struct {
	pthread_mutex_t lock;
	pthread_cond_t  cv_haswork;
	struct list_head queue;
} g_work_queue = {
	.lock = PTHREAD_MUTEX_INITIALIZER,
	.cv_haswork = PTHREAD_COND_INITIALIZER,
	.queue = LIST_HEAD_INIT(g_work_queue.queue),
};

// push item into work queue (return non-zero on error)
// (THREAD SAFE)
int wq_push(int n) {
	int ret = -1;
	WorkItem *wip = NULL;

	if ((wip = malloc(sizeof(WorkItem))) == NULL) {
		perror("malloc");
		goto cleanup;
	}
	wip->n = n;
	INIT_LIST_HEAD(&wip->entry);

	// CRITICAL SECTION
	//------------------
	pthread_mutex_lock(&g_work_queue.lock);
	list_add_tail(&wip->entry, &g_work_queue.queue);
	pthread_cond_signal(&g_work_queue.cv_haswork);
	pthread_mutex_unlock(&g_work_queue.lock);
	//------------------

	wip = NULL;	// don't free on exit from function
	ret = 0;	// success

cleanup:
	if (wip) free(wip);
	return ret;
}

// pop item from work queue (sleep until available OR should_quit)
// returns -1 if should_quit
// (THREAD SAFE)
int wq_pop() {
	int ret = -1;
	WorkItem *wip = NULL;

	pthread_mutex_lock(&g_work_queue.lock);

	// first - wait for list to be non-empty
	while (list_empty(&g_work_queue.queue)) {
		if (should_quit) goto cleanup;
		pthread_cond_wait(&g_work_queue.cv_haswork, &g_work_queue.lock);
	}

	// then - pop first item (will be free'd in the cleanup path)
	wip = list_entry(g_work_queue.queue.next, WorkItem, entry);
	list_del_init(&wip->entry);

	// return the value
	ret = wip->n;
cleanup:
	pthread_mutex_unlock(&g_work_queue.lock);
	if (wip) free(wip);
	return ret;
}

void quit_handler(int sig) {
	(void)sig;
	should_quit = 1;
}

void * worker_thread(void *_unused_arg) {
	(void)_unused_arg;
	int n;
	printf("[%d:%d] Worker thread starting\n", getpid(), gettid());
	while ((n = wq_pop()) > 0) {
		for (int i = 0; i < n; ++i) {
			printf("[%d:%d] request(%d) - %d\n", getpid(), gettid(), n, i);
			sleep(1);
		}
	}
	printf("[%d:%d] Worker thread DONE\n", getpid(), gettid());
	return NULL;
}

// for keeping a linked-list of thread objects to join on exit
typedef struct {
	pthread_t ptid;
	struct list_head entry;
} WorkerThread;

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	int workers = 0;
	LIST_HEAD(wthreads);

	// parse CLI argument
	if (argc < 2) {
		printf("usage: %s NUM_WORKERS\n", argv[0]);
		goto cleanup;
	}
	workers = atoi(argv[1]);
	if ((workers <= 0) || (workers > MAX_WORKERS)) {
		printf("bogus worker count %d\n", workers);
		goto cleanup;
	}

	// set up clean-shutdown signal handlers
	struct sigaction sa = { .sa_handler = quit_handler };
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	// spin up the workers
	for (int i = 0; i < workers; ++i) {
		WorkerThread *wtp = malloc(sizeof(WorkerThread));
		if (wtp == NULL) {
			perror("malloc");
			goto cleanup;
		}
		INIT_LIST_HEAD(&wtp->entry);
		if (pthread_create(&wtp->ptid, NULL, worker_thread, NULL)) {
			perror("pthread_create");
			goto cleanup;
		}
		list_add(&wtp->entry, &wthreads);
	}

	// run main-listener-loop
	while (!should_quit) {
		int n;
		printf("[%d:%d] enter request: ", getpid(), gettid()); fflush(stdout);
		if (scanf("%d", &n) == 1) {
			if (wq_push(n)) goto cleanup;
		}
	}
	ret = EXIT_SUCCESS;
cleanup:
	printf("\n[%d:%d] QUIT(%d)\n", getpid(), gettid(), ret);

	// terminate all workers
	if (!list_empty(&wthreads)) {
		// ensure the quit flag is set (in case we got here via error path, not termination)
		should_quit = 1;
		
		// broadcast-signal all workers that we have "work" for them (wake up and quit)
		pthread_mutex_lock(&g_work_queue.lock);
		pthread_cond_broadcast(&g_work_queue.cv_haswork);
		pthread_mutex_unlock(&g_work_queue.lock);

		// now join each thread in turn, freeing resources as we go
		WorkerThread *wp, *tp;
		list_for_each_entry_safe(wp, tp, &wthreads, entry) {
			pthread_join(wp->ptid, NULL);	// ignoring return value
			free(wp);
		}
	}

	return ret;
}
