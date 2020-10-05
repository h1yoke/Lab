#!/bin/bash
ps ux | grep "*/sbin/*" | awk '{print $2}' > pid.info