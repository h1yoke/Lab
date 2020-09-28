#!/bin/bash
filename="/var/log/anaconda/X.log"
grep -E "*\(WW\)*" $filename | sed "s/(WW)/Warning:/g" > full.log
grep -E "*\(II\)*" $filename | sed "s/(II)/Information:/g" >> full.log