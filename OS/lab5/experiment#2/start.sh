#!/bin/bash
if [[ $# -ne 1 ]]; then
  echo "Wrong input!"
  exit 1
fi

K=$1
N=3100000

for ((i=0; i < $K; i++)); do
  echo $i" process has started"
  (bash newmem.bash $N) &
done
