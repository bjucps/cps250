#include <stdio.h>
#include <stdlib.h>

int main()
{
  int exitcode;
  
  printf("Getting ready to run a command...\n");
  exitcode = system("ls -l /home");
  printf("command finished with exit code %d\n", exitcode);


}
