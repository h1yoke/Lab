#!/bin/bash
ps aux | awk '{print $2 " " $11}' | grep "/sbin/" | awk '{print $1}' > 2.info