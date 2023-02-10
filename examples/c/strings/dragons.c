#include <stdio.h>
#include <string.h>

int main() {
    char buff10[10];
    char buff20[20];
    char message[80];

    strcpy(buff10, "hi ");      // buff10 = "hi " (fine: need room for 3+1 chars, have 10)
    strcpy(buff10, "there!");   // buff10 += "there!" (still OK: need room for 9+1 chars, total, and have exactly that)
    sprintf(message, "buff10 = '%s' (%zu chars of string, %zu chars of space)", buff10, strlen(buff10), sizeof(buff10));
    puts(message);

    strcpy(buff20, buff10);     // buff20 = buff10 (fine; need room for 9+1 chars, have 20)
    strcat(buff20, buff10);     // buff20 += buff10 (still OK; need room for 18+1 chars, have 20)
    sprintf(message, "buff20 = '%s' (%zu chars of string, %zu chars of space)", buff20, strlen(buff20), sizeof(buff20));
    puts(message);

    // TROUBLE STARTS HERE

    strcpy(buff10, buff20);     // OOPS: need room for 18+1 chars, have only 10 (no warning, just BOOM, maybe)
    strcat(buff20, "!!");       // OOPS: need room for 20+1 chars total, have only 20 (no warning, just BOOM, maybe)

    strcpy(buff20, "AAAAAAAAAAAAAAAAAAA"); // Need 19+1, have 20 (OK)
    sprintf(message, "%s-%s-%s-%s-%s", buff20, buff20, buff20, buff20, buff20); // Need 99+1, have only 20 (BOOM, maybe)
   
    return 0;
}
