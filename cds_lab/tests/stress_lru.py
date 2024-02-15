#!/usr/bin/env python3
import random
import string
import sys


def gen_word(n: int) -> str:
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(n))


try:
    nchars = int(sys.argv[1])
    nwords = int(sys.argv[2])
    nlines = int(sys.argv[3])
except (IndexError, ValueError):
    print(f"usage: {sys.argv[0]} WORD_LEN NUM_WORDS NUM_LINES")
    exit()

words = [gen_word(nchars) for _ in range(nwords)]
for _ in range(nlines):
    print(random.choice(words))

