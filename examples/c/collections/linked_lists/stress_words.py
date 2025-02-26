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

    gcount = max(10, nwords // 3)
    raw_pool = [random_word() for _ in range(gcount)]
    parted_pool = { P:[] for P in PARTS }
    for word in raw_pool:
        parted_pool[random.choice(PARTS)].append(word)
    for P in PARTS:
        if not parted_pool[P]:
            del parted_pool[P]
    used_parts = list(parted_pool.keys())
    
    while gcount > 0:
        part = random.choice(list(parted_pool))
        ppool = parted_pool[part]
        pavail = len(ppool)
        pcount = random.randint(1, min(pavail, 7))
        pwords = ppool[:pcount]
        del ppool[:pcount]
        if not ppool:
            del parted_pool[part]
        gcount -= pcount
        print(f"{part}: {' '.join(pwords)}")

    print()

    parts_with_word = used_parts + ['word']
    for _ in range(nwords):
        print(random.choice(parts_with_word))


if __name__ == "__main__":
    main(sys.argv)

