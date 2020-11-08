#!/bin/bash
grep "VmSize:[[:space:]]\+[0-9]\+" /proc/*/status |
  awk -F ':' '{print $1 $3}' |
  sort -n -k 2 | tail -n 1