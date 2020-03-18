#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int ret = 1;

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("unable to open file");
        goto cleanup;
    }

    char c = '\0';
    while (read(fd, &c, 1) == 1) {
        write(1, &c, 1);
    }

    ret = 0;
cleanup:
    if (fd >= 0) close(fd);
    return ret;
}
