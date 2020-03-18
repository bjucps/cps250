#include <string.h>
#include <stdio.h>
#include <bsd/string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   if (argc != 3) {
     printf("Usage: concat file1 file2\n");
     exit(1);
   }

   char *file1 = argv[1];
   char *file2 = argv[2];

   char buf[50];
   snprintf(buf, sizeof(buf), "%s is %s", file1, file2);
 
   printf("buf = %s\n", buf);

   strlcpy(buf, file1, sizeof(buf));
   strlcat(buf, " is ", sizeof(buf));
   strlcat(buf, file2, sizeof(buf));

   printf("buf = %s\n", buf);


}
