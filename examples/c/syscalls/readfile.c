#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char **argv) {
  char ch[1];
  int result;
  int fd;
  
  if (argc != 2) {
    puts("usage: readfile <filename>");
    exit(1);
  }
  
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    puts("file not found.");
    exit(1);
  }
  
  while ((result = read(fd, ch, 1)) > 0) {
    
    write(1, ch, 1);
    
  } 
  
  close(fd);

  return 0;
}

