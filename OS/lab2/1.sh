#!/bin/bash
proc=$(ps aux | grep "user*[[:alnum:]]*")
wc -l <<< $proc > 1.info
awk '{print $2 ":" $11}' <<< $proc >> 1.info