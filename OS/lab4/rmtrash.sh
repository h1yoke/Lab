#!/bin/bash
if [[ $# -ne 1 ]]
then
  echo -e "Wrong input! Example: bash rmtrash.sh <filename>"
  exit 1
fi

tdir=~/.trash
cdir=$(pwd)
lname=$(date +"%s")

[ -d $tdir ] || mkdir $tdir
ln $cdir/$1 $tdir/$lname && echo \'$1\'" was successfully removed to trash."
rm $1
echo -e $cdir/$1" "$lname >> ~/.trash.log
