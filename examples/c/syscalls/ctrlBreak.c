#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

void handle_ctrlbreak(int signum) {
  // code to respond -- signum is the signal that triggered this function
	puts("Got the signal");
	fflush(stdout);
	//exit(1);
}

int main()
{

  pid_t pid;
  char buf[80];
  
  signal(SIGINT, handle_ctrlbreak);
	while(1) ;

}
