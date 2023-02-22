#include <stdio.h>

#define ARRSIZE 7

int main()
{ 
  int i = 0;
  int a[ARRSIZE];

  printf("Press enter to begin...");
  getchar();
  while (i <= ARRSIZE) {
    a[i++] = -1;
  }
  printf("after while\n");
}
