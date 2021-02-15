#include <stdio.h>
#include <string.h>

char namelist[5][10] = { "Matthew", "Mark", "Luke", "John" };

void printarr(char namelist[][10])
{
  int i;
  for (i = 0; i < 5; i++) {
    printf("%d - %s\n", i, namelist[i]);
  }
  
  
}

int main()
{
  int i = 0;

  printarr(namelist);  
  strcpy(namelist[1], "Freddie");
  printf("%c == %c\n", namelist[0][10], namelist[1][0]);
  printf("sizeof namelist[0] == %ld\n", sizeof(namelist[0]));
  strcpy(namelist[4], "Fred");
  printf("%s\n", namelist[4]);
      
  
}

