#!/bin/bash
echo $(cat /var/log/*.log | wc -l)