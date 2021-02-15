#include <stdio.h>
#include <string.h>

char *namelist2[5] = { "Matthew", "Mark", "Luke", "John" };

void printarr(char **namelist)
{
  int i;
  for (i = 0; i < 5; i++) {
    printf("%d - %s\n", i, namelist[i]);
  }
  
}

int main()
{
  int i = 0;
  char buf[30];

  // Don't do this:
  // strcpy(namelist2[0], "Abe");

  printarr(namelist2);  
  
  // Don't do this:
  // printf("%c\n", namelist2[0][10]);

  printf("sizeof namelist2[0] == %ld\n", sizeof(namelist2[0]));

  // Must allocate memory for namelist2[4] before writing to it
  namelist2[4] = buf;
  strcpy(namelist2[4], "Fred");
  printf("%s\n", namelist2[4]);
  
}

