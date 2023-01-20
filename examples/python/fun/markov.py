#!/usr/bin/env python3
import argparse
import random
import sys
from collections import Counter, defaultdict


class Markovinator:
    def __init__(self, sliding_window: int):
        self._w = sliding_window
        self._table = defaultdict(Counter)
    
    def ingest(self, seqiter):
        def _windowiter():
            for seq in seqiter:
                window = (None,)*(self._w + 1)
                for item in seq:
                    window = window[1:] + (item,)
                    yield window
                window = window[1:] + (None,)
                if not all(w is None for w in window):
                    yield window
        raw_table = Counter(_windowiter())
        for window, count in raw_table.most_common():
            self._table[window[:-1]].update({window[-1]: count})
    
    def generate(self):
        state = (None,)*self._w
        while True:
            odds = self._table[state]
            if not odds:
                raise ValueError(f"dead state {repr(state)}")
            winner = random.randrange(0, odds.total())
            for symbol, count in odds.most_common():
                winner -= count
                if winner <= 0:
                    if symbol is None:
                        return
                    yield symbol
                    state = state[1:] + (symbol,)
                    break


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument("-w", "--window", type=int, default=3, help="sliding window size")
    ap.add_argument("-s", "--sentences", action="store_true", default=False, help="parse/generate sentences, not words")
    ap.add_argument("count", type=int, help="how many entities to generate")
    args = ap.parse_args(argv[1:])

    m = Markovinator(args.window)
    if args.sentences:
        m.ingest(line.split() for line in sys.stdin)
    else:
        m.ingest(line.strip() for line in sys.stdin)

    for i in range(args.count):
        print((" " if args.sentences else "").join(m.generate()))


if __name__ == "__main__":
    main(sys.argv)
