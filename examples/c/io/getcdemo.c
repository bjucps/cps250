#include <stdio.h>

int main()
{
  int ch;

  puts("Enter some data:");
  ch = getchar();
  puts("You entered:");
  while (ch != '\n'  && ch != EOF) {
    printf("%c (%d)\n", ch, ch);
    ch = getchar();
  }   


}
