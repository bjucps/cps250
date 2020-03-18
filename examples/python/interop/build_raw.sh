#!/bin/sh
gcc -fpic -shared -ocrunch.so crunchraw.c
gcc -g -ocrunch crunchraw.c crunchprog.c


