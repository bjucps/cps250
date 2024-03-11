/* waitbad.c
 * - Must be compiled/linked with POSIX Threads (-lpthread)
 * - Demonstrates inefficient approach to waiting for a thread's work to complete
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long num = 0;               // shared N used by both halves of the 3n+1 algorithm
pthread_mutex_t num_lock;   // Mutex protecting `num`

void *alg_3nplus1(void *unused) {
	(void)unused;
	unsigned long long ticks = 0u;
	unsigned long long tocks = 0u;

	pthread_mutex_lock(&num_lock);
	while (num > 1) {
		++ticks;
		if ((num & 1) == 1) { // is ODD
			++tocks;
			long new = 3 * num + 1;
			printf("3 * %ld + 1 -> %ld\n", num, new);
			num = new;
		}
		pthread_mutex_unlock(&num_lock);
		pthread_mutex_lock(&num_lock);
	}
	pthread_mutex_unlock(&num_lock);
	printf("alg_3nplus1: %llu / %llu\n", tocks, ticks);
	return NULL;
}

void *alg_div2(void *unused) {
	(void)unused;
	unsigned long long ticks = 0u;
	unsigned long long tocks = 0u;

	pthread_mutex_lock(&num_lock);
	while (num > 1) {
		++ticks;
		if ((num & 1) == 0) { // is EVEN
			++tocks;
			long new = num / 2;
			printf("%ld / 2 -> %ld\n", num, new);
			num = new;
		}
		pthread_mutex_unlock(&num_lock);
		pthread_mutex_lock(&num_lock);
	}
	pthread_mutex_unlock(&num_lock);
	printf("alg_div2: %llu / %llu\n", tocks, ticks);
	return NULL;
}

int main(int argc, char *argv[]) {
	int ret = EXIT_FAILURE;
	pthread_t t1, t2;
	pthread_mutex_init(&num_lock, NULL);

	if (argc < 2) {
		printf("usage: %s N\n", argv[0]);
		goto cleanup;
	}

	errno = 0;
	num = strtoul(argv[1], NULL, 10);
	if (errno) {
		perror("strtoul");
		goto cleanup;
	}

	if (pthread_create(&t1, NULL, alg_3nplus1, NULL)) {
		perror("pthread_create");
		goto cleanup;
	}
	if (pthread_create(&t2, NULL, alg_div2, NULL)) {
		perror("pthread_create");
		goto cleanup;
	}

	if (pthread_join(t1, NULL)) { perror("pthread_join"); goto cleanup; }
	if (pthread_join(t2, NULL)) { perror("pthread_join"); goto cleanup; }

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}
