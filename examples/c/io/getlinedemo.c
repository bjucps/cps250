#include <stdio.h>

/*
 * inputline(buf, bufSize)
 * - Reads one complete line from stdin
 * - Stores up to <bufSize>-1 characters from input line in <buf> and discards remainder
 * - Null terminates buf; strips out terminating line feed
 * - Note: Does not handle EOF / error conditions
 */
void inputline(char* buf, size_t bufSize) 
{
    int numRead = 0;
    int ch = 0;
    
    while (numRead < bufSize - 1 && ch != '\n') {
        ch = getchar();
        buf[numRead] = ch;
        ++numRead;
    }
    
    if (ch == '\n') {
        buf[numRead-1] = 0; // replace newline with null terminator
    } else {
        buf[bufSize-1] = 0; // ensure buffer is properly null terminated
    }
    
    while (ch != '\n') {
        ch = getchar();
    }
}

main()
{
  char ch;
  char buf[5];
    

  puts("Enter some data:");
  inputline(buf, sizeof(buf));
  puts("You entered:");
  puts(buf);
  puts("Enter some data:");
  inputline(buf, sizeof(buf));
  puts("You entered:");
  puts(buf);

}
