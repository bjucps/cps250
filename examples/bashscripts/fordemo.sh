#!/bin/bash

for i in cat dog tiger giraffe
do
  echo In the loop
  echo "i's value is $i"
done

echo "You typed the following $# arguments:"
for i in $*
do
  echo $i
done
