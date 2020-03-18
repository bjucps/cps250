#!/bin/bash


echo -n "What is your name? "
read name;   # get user's name from keyboard

while [ "$name" = "" ]
do
  echo -n "Please tell me your name:"
  read name
done

echo "Hello, $name, nice to meet you."
