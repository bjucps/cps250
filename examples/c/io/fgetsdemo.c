#include <stdio.h>

int main()
{
  char ch;
  char buf[5];

  puts("Enter some data:");
  fgets(buf, sizeof(buf), stdin);
  printf("You entered: '%s'", buf);
  puts("Enter some data:");
  fgets(buf, sizeof(buf), stdin);
  printf("You entered: '%s'", buf);



}
