#include <stdio.h>

//#define DEBUG 56

#define ADD(x, y) ((x) + (y))
#define SQUARE(x) ((x) * (x))
int main()
{
    int count = 0;
    puts("Hello");
    printf("%d", DEBUG);
    printf("%d", ADD(2, 2) * 4);
    printf("%d", SQUARE(++count));
    //puts(253);
    #ifdef DEBUG
    puts("Got here!");
    #endif
    puts("We who are about to die salute you.");
}
