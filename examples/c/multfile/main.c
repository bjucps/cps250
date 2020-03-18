#include <stdio.h>

#include "util.h"



//extern int hiImaGlobal;

//int showmenu(double); // function prototype

int main()
{
    puts("Hello, world!");
    showmenu(3);
    #ifdef DEBUG
    fprintf(stderr, "Got here!\n");
    #endif
    printf("hiImaGlobal = %d\n", hiImaGlobal);
}
