#!/bin/bash
CMD="./robcmp-simavr-debug -c 16000000 -m atmega328p -f $2"

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"

echo -n "               $1 "
if [ "${V}0" -eq 10 ]; then
    make $2
else
    make -s $2
fi

if [ "$?" -eq 0 ]; then
    if [ "$V" = "1" ]; then
        ${CMD}
    else
	    timeout 10s ${CMD} &> /dev/null
    fi
    STATUS=$?
	if [ "${STATUS}" -eq 0 ]; then
		echo -e \\r${GREEN}[PASS]\\t\\t${NC}
	else
		echo -e \\r${RED}[FAILED] ${STATUS}\\t${NC}
	fi
else
	echo -e \\r${RED}[BUILD FAILED]\\t${NC}
fi

