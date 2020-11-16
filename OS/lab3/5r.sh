#!/bin/bash
mode="+"
val=1
(tail -f 5p) |
  while true;
  do
    read LINE
    case $LINE in
    "MUL")
      mode="*"
    ;;
    "ADD")
      mode="+"
    ;;
    "QUIT")
      echo "'QUIT' message was recieved."
      echo "result: "$val
      exit 0
    ;;
    "ERRQUIT")
      echo "Syntax error: unrecognized string token."
      exit 1
    ;;
    *)
      if [[ $mode == "+" ]]
      then
        val=$((val + LINE))
      else
        val=$((val * LINE))
      fi
    ;;
    esac
  done

