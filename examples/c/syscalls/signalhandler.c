#include <signal.h>
#include <stdio.h>

int ctrlcpressed = 0;

void handlectrlc(int sig)
{
  printf("Ctrl-C Pressed!\n");
  ctrlcpressed = 1;
}

void waitforawhile(int len) {
    int i;
    int j;
    for (i = 0; i < 10000; i++) 
      for (j = 0; j < len; j++)
        ;
}

int main()
{  
  signal(SIGINT, handlectrlc);
  
  while (!ctrlcpressed) {
    printf("Waiting for ctrl-c...\n");
    sleep(10);
     printf("Returned from sleep...\n");
    //waitforawhile(500000);
  }
  
  printf("Graceful shutdown complete.\n");

}
