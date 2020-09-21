#!/bin/bash
while [[ "$a" != "q" ]]; do
  str="$str$a"
  read a
done
echo $str
