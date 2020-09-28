#!/bin/bash
cut -d ':' -f 1,3 < /etc/passwd | sort -n -t ':' -k 2