#!/bin/bash
## tcsh script: clean
## helps to rm unwanted files from a directory

# Right number of parameters?
if ($# != 1) then
  echo usage: $0 directory; exit 1
endif

set dir = $1
if (! -d $dir || ! -w $dir) then
  echo $dir must be a writable directory.
  echo usage: $0 directory; exit 1
endif
cd $dir
#set files = *

for file in *
do
  if (! -f $file) then
    echo $file is not a file, skipping
    continue
  else
    if (! -w $file) then 
      echo $file is write-protected. It has been skipped.
      continue
    endif
  endif
  echo " " ## gives a blank line
  /bin/ls -l $file
  while(1) ## infinite loop
    echo -n "***** Delete $file or not?? [y, n, m, t, !, ?, or q]" :
    read c
    case $c in
      y) ## yes -- remove the file
#        rm -f $file
        if (-e $file); then
          echo cannot delete $file
        else
          echo "***** $file deleted"
        fi
        break ## go to next file
        ;;
      n) ## no, do not delete the file
        echo "***** $file deleted anyways!"
        break ## to handle next file
        ;;
      m) ## display file with more
        more $file; continue  ## back to while loop
        ;;
      t) ## show tail of file
        tail $file; continue  ## back to while loop
        ;;
      q) ## quit from clean
        exit 0
        ;;
      *) ## help for user
        echo "clean commands: followed by RETURN\
          y	yes delete file\
          n	no, do not delete the file, skip to next\
          m	display file with more first\
          t	display tail of file first\
          q	quit, exit from clean"
    esac
  end ## of while
done ## of foreach
   
