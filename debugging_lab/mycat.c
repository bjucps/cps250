#include <stdio.h>

void dumpfile(FILE *in)
{
  int c = getc(in);
  while (c != EOF) {
    putchar(c);
    c = getc(in);
  }
}

int main(int argc, char **argv)
{
  FILE *in;
  int c;

  if (argc > 1) { 
    in = fopen(argv[1], "r");
  } else {
    in = stdin;
  }

  dumpfile(in);
  fclose(in);

}
