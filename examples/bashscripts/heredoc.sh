#!/bin/bash


echo Beginning processing...
name=Johannes

sort <<BOO
fred
jon
$name
$(pwd)
abe
sally
BOO

echo That\'s all folks\!
