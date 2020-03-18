#!/bin/bash

function Hello {
  local MYNAME

  echo "What is your name?"
  read MYNAME
  echo "Hello, $MYNAME"
}

function FancyHello {
  local FIRSTNAME LASTNAME
  FIRSTNAME=$1
  LASTNAME=$2

  echo "Hello, $FIRSTNAME $LASTNAME"
}

#Hello
FancyHello Mary Baker

