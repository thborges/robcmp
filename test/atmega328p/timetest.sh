#!/bin/bash
CMD="./robcmp-simavr-debug -c 16000000 -m atmega328p -f $2"

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

echo -n "               $1 "
timer=0
make -s $2
REP=10
if [ "$?" -eq 0 ]; then
    if [ "$V" = "1" ]; then
        ${CMD}
    else
	    timeout 10s ${CMD} &> /dev/null
    fi
    STATUS=$?
	if [ "${STATUS}" -eq 0 ]; then

		TIMEFORMAT="%U" # get only the User time
		for i in $(seq 1 $REP); do
			timer=$timer+$({ time $CMD &>/dev/null; } 2>&1)
		done
		timer=$(echo "${timer//,/.}")
		avg=$(echo "scale=3;($timer)/$REP -q"| bc)
		
		echo -e \\r${GREEN}[PASS]\\t\\t${NC}\\t\\t\\t${avg}
	else
		echo -e \\r${RED}[FAILED] ${STATUS}\\t${NC}
	fi
else
	echo -e \\r${RED}[BUILD FAILED]\\t${NC}
fi