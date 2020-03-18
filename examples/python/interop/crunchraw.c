// Non-Python Module simple C library

// Implement our crunch hash function in C
unsigned int crunch(unsigned char *buff, unsigned int blen) {
    unsigned int i = 0;
    unsigned int val = 0xDEADBEEFL;

    for (; i < blen; ++i) {
        val += buff[i];
        val = ((val << 5) | (val >> 27)) & 0xffffffff;
    }

    return val;
}

