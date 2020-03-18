#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main(int argc, char **argv)
{


  char *args[3] = { "/usr/bin/gedit", "execdemo.c", NULL };
  printf("Hi, I'm the process who is about to die!\n");
  execv(args[0], args);
  printf("Hmmm ... something went wrong ... I'm ALIVE!!\n");

}
