#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
  int result;
  int i;
  
  printf("Getting ready to fork()...\n");
  fflush(stdout);
  result = fork();
    
  if (result == 0) {
    // child process
    for (i = 0; i < 5; i++) {
      printf("Hi! I'm the child...\n");
    }
  } else if (result > 0) {
    // original (parent)
    for (i = 0; i < 5; i++) {
      printf("Hi! I'm the parent, and my child is known as pid: %d...\n", result);
    }
    getchar();
    waitpid(result, NULL, 0);
    printf("My child has died.\n");
  } else {
    // fork failed
    printf("Oops -- fork failed.");
  }

  return 0;
}
