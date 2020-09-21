#!/bin/bash
echo -e "1 - nano\n2 - vim\n3 - links\n0 - exit\nChoose action: "
read input
case "$input" in
"1" ) /usr/bin/nano;;
"2" ) /usr/bin/vi;;
"3" ) /usr/bin/links;;
esac
