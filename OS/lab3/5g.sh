#!/bin/bash
mkfifo 5p 2> /dev/null

while true;
do
  read LINE
  case $LINE in
  \*)
    # multiplying
    echo "MUL" > 5p
  ;;
  +)
    # adding
    echo "ADD" > 5p
  ;;
  *)
    # format number
    sign="+"
    if [[ ${LINE:0:1} == "-" || ${LINE:0:1} == "+" ]]
    then
      sign=${LINE:0:1}
      LINE=${LINE:1}
    fi

    # parse number or string
    token=$(tr -d '0-9' <<< $LINE)
    if [[ -n $token ]]
    then
      if [[ $token == "QUIT" ]]
      then
        # quit
        echo "QUIT" > 5p
        exit 0
      else
        # unrecognized string token
        echo "ERRQUIT" > 5p
        echo "Syntax error: unrecognized string token."
        exit 1
      fi
    else
      # number
      echo $sign$LINE > 5p
    fi
  ;;
  esac
done

