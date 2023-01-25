#!/bin/bash


echo Beginning processing...
name=Johannes

echo ------------------
sort <<BOO
fred
jon
$name
$(pwd)
abe
sally
BOO

echo ------------------
echo That\'s all folks\!
