#!/bin/bash
regex="[[:alnum:]_]\+@[.[:alnum:]_]\+"
grep -oh -s $regex /etc/* | grep -oh $regex | tr '\n' ',' > emails.lst