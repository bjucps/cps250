#include <stdio.h>

int main()
{
  char buf[5];
  int size;
  
  buf[4] = 'x';
  size = snprintf(buf, sizeof(buf), "Testy");
  if (buf[4] != '\0') {
    printf("Not null terminated!\n");
  } else {
    printf("Result: '%s' (%d)\n", buf, size);
  }

}