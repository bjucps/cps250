#!/usr/bin/env python3
"""generate random stress-testing inputs for the `words.c` example program
"""
import random
import string
import sys

PARTS = ['noun', 'verb', 'adjective', 'adverb']

def random_word() -> str:
    nchars = random.randint(5, 15)
    return "".join(random.sample(string.ascii_lowercase, nchars))


def main(argv):
    try:
        nwords = int(argv[1])
    except (IndexError, ValueError):
        print(f"usage: {argv[0]} NWORDS")
        exit(1)

    dmax = max(10, nwords // 3)
    dcount = 0
    while dcount < dmax:
        part = random.choice(PARTS)
        pcount = random.randint(1, min(dmax - dcount, 7))
        dcount += pcount
        pwords = [random_word() for _ in range(pcount)]
        print(f"{part}: {' '.join(pwords)}")

    print()

    parts_with_word = PARTS + ['word']
    for _ in range(nwords):
        print(random.choice(parts_with_word))


if __name__ == "__main__":
    main(sys.argv)

