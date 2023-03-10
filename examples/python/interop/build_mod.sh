#!/bin/sh
gcc -fpic -shared -I/usr/include/python3.7 -ocrunchlib.so crunchlib.c

