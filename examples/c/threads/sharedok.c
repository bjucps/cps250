/* sharedok.c
 * - Must be compiled and linked with threads library like this:
 *   gcc sharedok.c -lpthread -o sharedok
 */
 
#include <stdio.h>
#include <pthread.h>

#define LOOPS 64*1024*1024

void *add_em_up(void *); 
void *sub_em_down(void *); 

long num = 0;  // shared variable

pthread_mutex_t num_lock;   // Mutex protecting shared variable

int main() {
  pthread_t thread1, thread2, thread3, thread4;

  pthread_mutex_init(&num_lock, NULL);
       
  pthread_create(&thread1, NULL, add_em_up, NULL);
  pthread_create(&thread2, NULL, sub_em_down, NULL);
  pthread_create(&thread3, NULL, add_em_up, NULL);
  pthread_create(&thread4, NULL, sub_em_down , NULL);

  // Now, wait for threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  pthread_join(thread4, NULL);

  printf("num = %ld\n", num);
}
				
void *add_em_up(void *ptr) {
  for (int i = 0; i < LOOPS; i++) {
    pthread_mutex_lock(&num_lock);
    ++num;
    pthread_mutex_unlock(&num_lock);
  }
}

void *sub_em_down(void *ptr) {
  for (int i = 0; i < LOOPS; i++) {
    pthread_mutex_lock(&num_lock);
    --num;
    pthread_mutex_unlock(&num_lock);
  }
}

