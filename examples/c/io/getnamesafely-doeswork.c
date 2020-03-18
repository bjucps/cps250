#include <stdio.h>
#include <string.h>

main()
{
  int c;
  char name[6];
  int i;
  int okname = 0;
  
  while (!okname) {
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    if (name[strlen(name)-1] != '\n') {
      printf("Sorry, your name is too long. Try again.\n");
      while (c != '\n')
        c = getchar();
    } else {
      okname = 1;
    }
  }
  
  printf("Hello, %s\n", name);
}
