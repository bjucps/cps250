#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

int childdone = 0;

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
    printf("I am the child; what is your name?");
    fgets(buf, 79, stdin);
    printf("Hello, %s, pleased to meet you.\n", buf);
    kill(getppid(), SIGUSR1);
    printf("Child waiting for ENTER.");
    fgets(buf, 79, stdin);
    printf("Child terminating...\n");

  } else {
    // I'm the parent

    printf("I am the parent and I shall wait for a signal.\n");
    for ( ; !childdone; ) {
      sleep(1);

    }
    printf("I am the parent and my child sent me a signal.\n");
    wait(NULL);
    printf("The child has exited.\n");

  }

}
