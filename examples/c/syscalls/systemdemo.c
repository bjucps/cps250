#include <stdio.h>
#include <unistd.h>

main()
{
  int exitcode;
  
  printf("Getting ready to run a command...\n");
  exitcode = system("ls -l /home");
  printf("command finished with exit code %d\n", exitcode);


}
