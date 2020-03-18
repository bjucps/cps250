#!/bin/sh
gcc -fpic -shared -I/usr/include/python3.6 -ocrunchlib.so crunchlib.c

