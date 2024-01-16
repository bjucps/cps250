#include <stdio.h>
#include <stdlib.h>

int main() {
  char buf[80];
  FILE *f = fopen("stuff.txt", "r");

  printf("Program running.\n");
  if (f == NULL) {
    fprintf(stderr, "Can't open stuff.txt...\n");
    return 1;
  }

  if (fgets(buf, 79, f)) {
      printf("%s", buf);
  } else {
      perror("fgets");
  } 

  return 0;
}
