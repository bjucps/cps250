#include <stdio.h>
#include <stdlib.h>

main(int argc, char **argv)
{
  int ch;
  char buf[5];
  FILE *in;
  char *result;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: fgetsdemowithfile <filename>\n");
    exit(1);
  }

  if ((in = fopen(argv[1], "r")) != NULL) {
  
    result = fgets(buf, sizeof(buf), in);
    while (result != NULL) {
     printf("%s", buf);
     result = fgets(buf, sizeof(buf), in);
    }
    if (ferror(in)) {
      perror("Problem reading file...");
    }
    fclose(in);
  } else {
    //printf("Sorry, no such file in sight!\n"); 
    // Better:
    perror("Unable to open file");
  }


}
