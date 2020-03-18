#include <stdio.h>

char *namelist[5] = { "Matthew", "Mark", "Luke", "John" };

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

  printarr(namelist);  
  printf("%c\n", namelist[0][30]);
  namelist[4] = (char*)malloc(30);
  sprintf(namelist[4], "%s and %s", namelist[0], namelist[1]);
  printf("%s\n", namelist[4]);
  free(namelist[4]);
  
}

