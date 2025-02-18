#!/bin/bash

export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'

page=cat

if [ $# = 2 ]; then
  if [ "$1" = "-p" ]; then
    page=more
  fi
  filename="$2"
elif [ $# = 1 ]; then
  filename="$1"
else
  echo "usage: type <filename>"
  exit 1
fi

echo Filename is: \"$filename\"
echo "-----------------------------------"
$page "$filename"


