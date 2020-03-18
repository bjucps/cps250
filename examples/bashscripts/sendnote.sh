#!/bin/bash

function GenerateNote {
    local USERNAME
    local FNAME
    local LNAME
    
    USERNAME=$1
    FNAME=$2
    LNAME=$3

mail "$USERNAME@students.bju.edu" -s "A special personal note from your teacher" <<EONOTE
Dear $FNAME $LNAME,

I loved your solution. Keep up the good work.
Dr. Schaub
EONOTE

     echo "Sent your personal note to $FNAME $LNAME ($USERNAME)"
}

if [ $# = 0 ]
then
  echo "usage: sendnote.sh <username>+"
  exit 1
fi

for USERNAME in $*
do
    FULLNAME=$(grep $USERNAME /home/cps250/data/class.txt  |
                    awk -F, '{ print $5; }'  |
                    sort -u)
    LASTNAME=$(echo $FULLNAME | tr / ' ' | awk '{ print $1; }')
    FIRSTNAME=$(echo $FULLNAME | tr / ' ' | awk '{ print $2; }')

    GenerateNote $USERNAME $FIRSTNAME $LASTNAME
    
done





