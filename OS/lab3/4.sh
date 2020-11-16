#!/bin/bash
# run 3 bg loops
loop="while true; do a=$((10 * 2)); done"
(bash <<< $loop) &
(bash <<< $loop) &
(bash <<< $loop) &
echo $(pgrep -P $$)

# control first process
first_pid=$(pgrep -P $$ | head -n 1)
cur_prior=0
(while true;
do
  loaded=$(ps aux | awk '{ print $2 " " $3 }' | grep $first_pid | awk '{ print $2 }')
  if [[ $(echo $loaded > 10.0 | bc) -eq 1 ]]
  then
    cur_prior=$((cur_prior + 1))
    renice -n $cur_prior -p $first_pid &> /dev/null
  fi
  sleep 5
done) &

