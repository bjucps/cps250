/* hello.c
 * - Must be compiled and linked with threads library like this:
 *   gcc -ohello hello.c -lpthread
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_message_function(void *);

int main() {
  pthread_t thread1, thread2;

  //print_message_function("Hello");
  pthread_create(&thread1, NULL, print_message_function, "Hello");

  //print_message_function("World");
  pthread_create(&thread2, NULL, print_message_function, "World");

  // Now, wait for threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
}


void *print_message_function(void *ptr) {
  char *message = (char *)ptr;

  int pid = getpid();
  for (int i = 0; i < 500000; i++) {
    printf("%d: %s\n", pid, message);
  }
}

