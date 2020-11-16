#!/bin/bash
printf "Enter pid: "
read pid

depth=1
children=" "$(pgrep -P $pid)

while [[ -n $(tr -d ' ' <<< $children) ]]
do
  echo $depth" generation:"$children

  # next generation
  for p in $children
  do
    new_children=$new_children" "$(pgrep -P $p)
  done
  children=$new_children
  new_children=""

  depth=$((depth+1))
done

