#include <stdio.h>

int main()
{
  char name[10];
  int age;
  
  printf("Enter your name: ");
    
  //gets(name);
  fgets(name, sizeof(name), stdin);
  printf("Hello, %s!\n", name);
  
  printf("How old are you?");
  scanf("%d", &age);
  printf("Are you really %d years old?\n", age);
 
  return 0;
}
