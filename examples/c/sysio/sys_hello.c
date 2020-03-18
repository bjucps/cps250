#include <unistd.h>

int main() {
    char msg[] = "hello, world\n";
    write(1, msg, sizeof(msg) - 1);
    return 0;
}
