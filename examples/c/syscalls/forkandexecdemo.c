#include <stdio.h>
#include <unistd.h>

char *ARGS[] = { "/bin/ls", "-l", "/tmp", NULL };

main()
{
  int result;
  int i;
  
  printf("Getting ready to fork()...\n");
  result = fork();
  if (result == 0) {
    // child process
    result = execv("/bin/ls", ARGS);
    if (result < 0) {
      printf("Ouch! I couldn't execv the new program.\n");
    }
    
  } else if (result > 0) {
    // original (parent)
    // wait for child to finish
    waitpid(result, NULL, 0);
    printf("Ok, the child finished. Bye bye.\n");
  } else {
    // fork failed
    printf("Oops -- fork failed.");
  }


}
