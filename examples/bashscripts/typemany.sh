#!/bin/bash

page=cat

if [ $# -gt 1 ]; then
  if [ "$1" = "-p" ]; then
    page=more
    shift
  fi

elif [ $# = 0 ]; then
  echo "usage: type <filename>"
  exit 1
fi

# $page $*

for file in "$@"
do
  echo "--${file}-----------------"
  $page "$file"
done


