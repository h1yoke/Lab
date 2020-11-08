#!/bin/bash
result=""
for pid in $(ps -Ao pid)
do
  f1=/proc/$pid/status
  f2=/proc/$pid/sched
  ppid=$(grep -s "PPid:" $f1 | awk '{print $2}')

  if [[ -n $ppid  ]]
  then
    rtime=$(grep -s "sum_exec_runtime" $f2 | awk '{print $3}')
    switches=$(grep -s "nr_switches" $f2 | '{print $3}')

    if [[ $switches -ne 0  ]]
    then
      art=$(bc <<< "scale=5; $rtime / $switches")
      if [[ ${art:0:1} == "." ]]
      then
        art=0$art
      fi
    else
      art=0
    fi
    result=$result"ProcessID="$pid" : Parent_ProcessID="$ppid" : Average_Running_Time="$art"\n"
  fi
done 
echo -e $result | sort -t "=" -nk 3 > 4.info
