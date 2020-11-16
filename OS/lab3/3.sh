#!/bin/bash
crontab <<< "0-59/5 * * * "$(date +"%a")" bash /home/user/lab3/"$0

