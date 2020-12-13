#!/bin/bash
rep_file=report.log

rm -f $rep_file

i=0
array=()
while true; do
  if [[ i -gt 0 && $((i % 100000)) == 0 ]]; then
    echo ${#array[*]} >> $rep_file
  fi

  array+=(1 2 3 4 5 6 7 8 9 10)
  let i=$i+1
done
