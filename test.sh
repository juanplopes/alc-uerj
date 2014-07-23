#!/bin/bash

if [ $# -lt 1 ]; then
    EXERCICIOS=(
        1.1 1.2 1.3
        3.3 3.4
    )
    for i in "${EXERCICIOS[@]}"
    do
        echo Exercício $i... 
        g++ exercicio_$i.cpp && ./a.out < exercicio_$i.in | diff -bZB - exercicio_$i.out
    done
    exit 0
fi

g++ exercicio_$1.cpp && ./a.out < exercicio_$1.in

./a.out < exercicio_$1.in | diff -bZB - exercicio_$1.out && echo "   OK" || echo "   FAILED"



