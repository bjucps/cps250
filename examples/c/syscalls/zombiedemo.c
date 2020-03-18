#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main()
{

  pid_t pid;
  char buf[80];
  printf("Hi, I'm the parent, and I'm about to fork!\n");
  pid = fork();
  printf("Ok, back from fork, I got: %d\n", pid);
  if (pid == 0) {
    // I'm the new process
    printf("I am the child; I am done.");

  } else if (pid > 0) {
    // I'm the parent
    printf("I am the parent and I shall run until you stop me.\n");
    
    //wait(NULL);  
    //printf("Ok, wait returned.\n");
    while (1);

  } else {
    printf("Oops! Fork failed... ");
  }

}
