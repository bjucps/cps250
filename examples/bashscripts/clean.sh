#!/bin/bash
## helps to rm unwanted files from a directory

function handle_file {
  local file
  file="$1" ## arg 1: name of file to handle
  
  echo " " ## gives a blank line
  /bin/ls -l "$file"

  while true; do ## infinite loop
    echo -n "***** Delete $file or not?? [y, n, m, t, q, or ?]" :
    read c
    case "$c" in
      y) ## yes -- remove the file
        if [ ! -e "$file" ]; then
          echo cannot delete $file
        else
          echo "***** $file deleted"
          # rm -f "$file"  JK! not during our demonstration
        fi
        break ## done with this file
        ;;
      n) ## no, do not delete the file
        echo "***** $file deleted anyways!"
        break ## done with this file
        ;;
      m) ## display file with more
        less $file ## because less is more
        continue  ## back to while loop
        ;;
      t) ## show tail of file
        tail $file; continue  ## back to while loop
        ;;
      q) ## quit entire script
        exit 0
        ;;
      *) ## help for user
        cat <<EOF
clean commands: followed by RETURN
  y	yes delete file
  n	no, do not delete the file, skip to next
  m	display file with more first
  t	display tail of file first
  q	quit, exit from clean
EOF
	;;
    esac
  done ## of while
}

# Right number of parameters?
if [ $# -ne 1 ]; then
  echo "usage: $0 directory"; exit 1
fi

dir="$1"
if [ ! -d "$dir" ] || [ ! -w "$dir" ]; then
  echo "$dir must be a writable directory."
  echo "usage: $0 directory"; exit 1
fi

cd "$dir"

for file in *
do
  if [ ! -f "$file" ]; then
    echo "$file is not a file, skipping"
    continue
  elif [ ! -w "$file" ]; then 
    echo "$file is write-protected. It has been skipped."
    continue
  fi

  handle_file "$file"
done ## of foreach
   
