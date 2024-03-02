#!/usr/bin/env python3
from collections import defaultdict

line_no = 0
word_index = defaultdict(list)

while True:
    try:
        line = input().strip()
    except EOFError:
        break
    line_no += 1
    
    in_word = False
    word_chars = []
    for i, ch in enumerate(line):
        i += 1
        was_word = in_word
        in_word = ch.isalnum() or ch in "-'"
        if was_word and not in_word:
            word = ''.join(word_chars)
            word_index[word].append((line_no, i - len(word) + 1))
            word_chars.clear()
        elif in_word:
            word_chars.append(ch)

    if in_word:
        word = ''.join(word_chars)
        word_index[word].append((line_no, i - len(word) + 1))

for word, locations in word_index.items():
    hits = ' '.join(f'{ln}:{cn}' for ln, cn in locations)
    print(f'{word}\t{len(locations)}\t{hits}')
