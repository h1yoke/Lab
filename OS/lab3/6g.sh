#!/bin/bash
while true;
do
  read LINE
  case $LINE in
  +)
    kill -USR1 $(cat .6pid)
  ;;
  \*)
    kill -USR2 $(cat .6pid)
  ;;
  TERM)
    kill -SIGTERM $(cat .6pid)
    break
  ;;
  esac
done

