#!/bin/bash
ps aux | grep "*/sbin/*" | awk '{print $2}' > 2.info