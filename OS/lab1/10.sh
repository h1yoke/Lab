#!/bin/bash
man bash |
  tr -s '[:space:]' '\n' |
  grep -E "[[:alnum:]]+" |
  sort | uniq -c | sort -n -r |
  awk '{if (length($2) >= 4) print $2}' | head -n 3