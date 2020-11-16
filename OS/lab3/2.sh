#!/bin/bash
at "now +2 minutes" -f 1.sh
(tail -f ~/report) |
  while true; do
    read LINE
    echo $LINE
  done

