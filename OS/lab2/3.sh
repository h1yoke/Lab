#!/bin/bash
ps ux | sort -k 8 | head -n 1 | awk '{print $2}'