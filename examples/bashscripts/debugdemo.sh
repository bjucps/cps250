#!/bin/bash

# Note: Run this script using the -xv option, like this:
#  bash -xv debugdemo.sh -p users.txt letter.txt

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
  $page "$file"
done


