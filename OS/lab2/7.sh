#!/bin/bash

# get start state
start=$(date +"%s")
for pid in $(ps -Ao pid)
do
  if [[ $pid != "PID" ]]
  then
    mem=$(grep -s "read_bytes:" /proc/$pid/io | tr -dc '0-9')
    if [[ -n $mem ]]
    then
      state=$state$pid" "$mem" "
    fi
  fi
done

# wait 1 minute
sleep 60

# get new state and differences
i=0
for token in $state
do
  case $((i % 2)) in
  0)
    pid=$token
    cur_mem=$(grep -s "read_bytes:" /proc/$pid/io | tr -dc '0-9')
  ;;
  1)
    if [[ -n cur_mem ]]
    then
      mem_diff=$(bc <<< "$token - $cur_mem")
      new_state=$new_state$pid" "$mem_diff"\n"
    fi
  ;;
  esac
  i=$((i + 1))
done

# get 3 top values
echo -e $new_state > 7.temp
i=0
for token in $(sort -rnk 2 7.temp | head -n 3)
do
  case $((i % 2)) in
  0)
    pid=$token
  ;;
  1)
    cmd=$(ps aux | grep " "$pid" " | awk '{print $11}')
    echo -e $pid":"$cmd":"$token
  ;;
  esac
  i=$((i + 1))
done
rm -f 7.temp