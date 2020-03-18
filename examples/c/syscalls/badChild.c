#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int childdone = 0;
int *pChildDone = &childdone;

void handleusr1(int sig) {
  childdone = 1;
  printf("Process %d received signal %d ...\n", getpid(), sig);
}

int main()
{

  pid_t pid;
  char buf[80];
  
  signal(SIGUSR1, handleusr1);

  printf("Hi, I'm the parent, and I'm about to fork!\n");
  pid = fork();
  printf("Ok, back from fork, I got: %d\n", pid);
  if (pid == 0) {
    // I'm the new process
    printf("I am the child;");
printf("The address of pChildDone is %x\n", (unsigned int)pChildDone);
    *pChildDone = 1;
    printf("Child terminating...\n");

  } else {
    // I'm the parent

    printf("I am the parent and I shall wait for a signal.\n");
printf("The address of pChildDone is %x\n", (unsigned int)pChildDone);
    /*for ( ; !childdone; ) {
     sleep(1);

    }*/
    printf("I am the parent and my child sent me a signal.\n");
    wait(NULL);
    printf("The child has exited.\n");

  }

}
