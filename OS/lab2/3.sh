#!/bin/bash
i=0
for token in $(ps -Ao pid,ppid)
do
  case $((i % 2)) in
  0)
    pid=$token
  ;;
  1)
    if [[ $pid -ne $$ && $token -ne $$ ]]
    then
      result=$result"\n"$pid
    fi
  ;;
  esac
  i=$((i + 1))
done
echo -e $result | tail -n 1