#!/bin/sh
gcc -fpic -shared $(pkg-config --cflags python3) -ocrunchlib.so crunchlib.c

