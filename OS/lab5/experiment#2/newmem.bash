#!/bin/bash
if [[ $# -ne 1 ]]; then
  echo "Wrong input!"
  exit 1
fi

N=$1
array=()
while [[ ${#array[*]} -lt $N ]]; do
  array+=(1 2 3 4 5 6 7 8 9 10)
done
