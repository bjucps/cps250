#!/bin/bash


echo "You supplied: $# arguments."
echo "This script is called: $0"

echo "Argument #1: $1"
echo "Argument #2: $2"

echo "All the arguments as one string: $*"

for arg in "$@"	 # try replacing "$@" with $* and "$*" to see the differences
do
  echo "argument is: $arg"
done

exit 50

