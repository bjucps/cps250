#include <stdio.h>



main()
{
  int c;
  char name[6];
  int i;
  int okname = 0;
  
  while (!okname) {
    printf("Enter your name: ");
    c = getchar();
    i = 0;
    while ( c != '\n' && i < sizeof(name)-1 ) {
      name[i] = c;
      c = getchar();
      ++i;
    }
    if (c != '\n') {
      printf("Sorry, your name is too long. Try again.\n");
    } else {
      okname = 1;
    }
  }
  
  printf("Hello, %s\n", name);
}
