#!/bin/bash

# Note: Run this script like this:
#  bash -xv debugdemo.sh -p file1 file2

# Enable enhanced debugging output
export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'

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

for file in $*
do
  #$page "$file"
  echo "Processing $file..."
done


