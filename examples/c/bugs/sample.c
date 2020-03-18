#include <stdio.h>

int main()
{ 
  int i = 0;
  int a[10];

  printf("Press enter to begin...");
  getchar();
  //int x = 5 / i;
  while (i <= 10) {
    a[i++] = -1;
  }
  printf("after while\n");
}
