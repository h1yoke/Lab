#!/bin/bash
echo $$ > .6pid
val=1
add()
{
  val=$((val + 2))
}
mul()
{
  val=$((val * 2))
}
stop()
{
  echo "'SIGTERM' signal was recieved."
  echo "result: "$val
  rm .6pid
  exit 0
}

trap 'add' USR1
trap 'mul' USR2
trap 'stop' SIGTERM

while true; do sleep 1; done

