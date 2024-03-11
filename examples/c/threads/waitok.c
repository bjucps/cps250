/* waitbad.c
 * - Must be compiled/linked with POSIX Threads (-lpthread)
 * - Demonstrates efficient approach to waiting for a thread's work to complete (using CVs)
 */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long num = 0;               // shared N used by both halves of the 3n+1 algorithm
pthread_mutex_t num_lock;   // Mutex protecting `num`

pthread_cond_t cv_even;		// wait for even
pthread_cond_t cv_odd;		// wait for odd

void *alg_3nplus1(void *unused) {
	(void)unused;

	pthread_mutex_lock(&num_lock);
	while (num > 1) {
		// wait until the number is ODD
		while ((num & 1) != 1) {
			pthread_cond_wait(&cv_odd, &num_lock);
		}
		if (num == 1) break;
		// do 3n+1
		long new = 3 * num + 1;
		printf("3 * %ld + 1 -> %ld\n", num, new);
		num = new;
		// IFF even, signal EVEN
		if ((num & 1) == 0) {
			pthread_cond_signal(&cv_even);
		}
	}
	pthread_mutex_unlock(&num_lock);
	return NULL;
}

void *alg_div2(void *unused) {
	(void)unused;

	pthread_mutex_lock(&num_lock);
	while (num > 1) {
		// wait until number is EVEN
		while ((num & 1) != 0) {
			pthread_cond_wait(&cv_even, &num_lock);
		}
		// do n/2
		long new = num / 2;
		printf("%ld / 2 -> %ld\n", num, new);
		num = new;
		// IFF odd, signal ODD
		if ((num & 1) == 1) {
			pthread_cond_signal(&cv_odd);
		}
	}
	pthread_mutex_unlock(&num_lock);
	return NULL;
}

int main(int argc, char *argv[]) {
	int ret = EXIT_FAILURE;
	pthread_t t1, t2;

	pthread_mutex_init(&num_lock, NULL);
	pthread_cond_init(&cv_even, NULL);
	pthread_cond_init(&cv_odd, NULL);

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

	// signal EVEN/ODD per initial value
	pthread_mutex_lock(&num_lock);
	if ((num & 1) == 0) {
		pthread_cond_signal(&cv_even);
	} else {
		pthread_cond_signal(&cv_odd);
	}
	pthread_mutex_unlock(&num_lock);

	if (pthread_join(t1, NULL)) { perror("pthread_join"); goto cleanup; }
	if (pthread_join(t2, NULL)) { perror("pthread_join"); goto cleanup; }

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}
