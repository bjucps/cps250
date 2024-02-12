#include <stdio.h>
#include <bsd/bsd.h>

struct fatstr {
    char  *data;
    size_t size;
};

char storage[3][100] = { "hello", "hello", "hello" };

struct fatstr safe_strings[3] = {
    { storage[0], sizeof(storage[0]) },
    { storage[1], sizeof(storage[1]) },
    { storage[2], sizeof(storage[2]) },
};

void modify_string_value(struct fatstr *fs) {
    // we know where the buffer is (fs->data)
    // AND how big it is (fs->size)
    strlcat(fs->data, " world!", fs->size);
}

int main() {
    printf("prior: '%s'\n", safe_strings[0].data);
    modify_string_value(&safe_strings[0]);
    printf("after: '%s'\n", safe_strings[0].data);
}
