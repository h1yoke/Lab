#!/bin/bash
test_dir=$HOME/test/
date_time=$(date +"%d-%m-%Y_%H-%M")
mkdir $test_dir 2> /dev/null &&
  (echo "catalog test was created successfully" >> ~/report;
   touch $test_dir$date_time)

ping "www.net_nikogo.ru" -n 1 2> /dev/null ||
  echo $date_time': "www.net_nikogo.ru" is unreachable' >> ~/report

