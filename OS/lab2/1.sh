#!/bin/bash
proc=$(ps ux | grep "user*[[:alnum:]]*")
wc -l <<< $proc > user_proc.info
awk '{print $2 ":" $11}' <<< $proc >> user_proc.info