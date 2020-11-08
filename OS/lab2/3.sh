#!/bin/bash
ps aux | sort -rk 9 | head -n 2 | awk '{printf("%s %s\n", $2, $9)}'