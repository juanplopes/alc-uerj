#!/bin/bash

if [ $# -lt 1 ]; then
    success=0
    failed=0
    for f in $(ls *.cpp | sort -V)
    do

        BASE=$(basename $f .cpp)
        echo -n "$BASE... "
        if g++ $f && ./a.out < data/$BASE.in | diff - data/$BASE.out > /dev/null 
		then
        	echo OK
        	((++success))
		else
			echo FAILED
			((++failed))
		fi
    done
    echo "PASSED: $success; FAILED: $failed."
    exit $failed
fi

g++ exercicio_$1.cpp && ./a.out < data/exercicio_$1.in

./a.out < data/exercicio_$1.in | diff - data/exercicio_$1.out && echo "OK" || echo "FAILED"


