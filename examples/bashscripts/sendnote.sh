#!/bin/bash

export PS4='+(${BASH_SOURCE}:${LINENO}): ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'

function GenerateNote {
    local USERNAME
    local TITLE
    local FNAME
    local LNAME
    
    USERNAME="$1"
    TITLE="$2"
    FNAME="$3"
    LNAME="$4"

echo mail "$USERNAME@students.bju.edu" -s "A special personal note from your teacher" 
cat <<EONOTE
Dear $TITLE $FNAME $LNAME,

I loved your solution. Keep up the good work.

Dr. J
EONOTE

     echo "Sent your personal note to $FNAME $LNAME ($USERNAME)"
}

if [ $# = 0 ]; then
  echo "usage: sendnote.sh [USERNAME [...]]"
  exit 1
fi

for USERNAME in "$@"; do
    LASTNAME=$(grep "$USERNAME" students.tsv | cut -f 1)
    FIRSTNAME=$(grep "$USERNAME" students.tsv | cut -f 2)
    TITLE=$(grep "$USERNAME" students.tsv | cut -f 4 | sed 's/M/Mr./;s/F/Miss/')

    GenerateNote "$USERNAME" "$TITLE" "$FIRSTNAME" "$LASTNAME"
done

