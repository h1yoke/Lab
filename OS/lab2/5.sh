#!/bin/bash
file=$(cat 4.info | tr -d ":")
echo "" > 5.info

i=0
sum=0.0
last_ppid=0
count=0
for token in $file
do
  num_token=$(tr -dc '0-9.' <<< $token)
  
  case $((i % 3)) in
  0)
    line=$token
  ;;
  1)
    line=$line" : "$token
    ppid=$num_token
  ;;
  2)
    line=$line" : "$token
    
    if [[ $ppid -eq $last_ppid ]]
    then
      sum=$(bc <<< "$sum + $num_token")
      count=$((count + 1))
    else
      avg=$(bc <<< "scale=5; $sum / $count")
      echo "Average_Sleeping_Children_of_ParentID="$last_ppid" is "$avg >> 5.info
      last_ppid=$ppid
      sum=$num_token
      count=1
    fi
    echo $line >> 5.info
    line=""
  ;;
  esac
  i=$((i + 1))
done
avg=$(bc <<< "scale=5; $sum / $count")
echo "Average_Sleeping_Children_of_ParentID="$last_ppid" is "$avg >> 5.info
