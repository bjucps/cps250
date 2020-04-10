#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void process(char *arg)
{
  char buf[8];

  strcpy(buf, arg);
  printf("You entered: %s\n", buf);

}

int main(int argc, char **argv) {
  if (argc != 2) exit(1);
  process(argv[1]);
  puts("Returned from call.");
}
