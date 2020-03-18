#!/bin/bash
# Demonstrates the use of a function

FancyHello () {
  local MYNAME

  if ( test $# -gt 0 ); then
    for MYNAME in $*; do
      echo "Hello $MYNAME"
    done
  else
    echo "What is your name?"
    read MYNAME
    if ( test -z "$MYNAME" ); then
      echo "Hello world."
    else
      FancyHello $MYNAME
    fi
  fi
}

if (test $# -gt 0); then
  FancyHello $*
else
  FancyHello #"CpS 320 class"
fi

