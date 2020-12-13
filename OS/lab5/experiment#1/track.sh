#!/bin/bash
rm -f memtop.log

printf "Press any key to en tracking..."
while [[ -z $LINE ]]; do
  echo "===============================" >> memtop.log
  top -b -d 1 -c | head -n 12 >> memtop.log
  read -t 0.25 -N 1 LINE
done
dmesg | grep "bash" | tail -n 2 >> memtop.log
