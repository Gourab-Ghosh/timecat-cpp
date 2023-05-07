#!/bin/sh

debug=false
# debug=true

rm ./a.out

if $debug
then
    printf "\nCompiling in Debugging Mode...\n"
    /usr/bin/g++ -g -Wall test.cpp
    # /usr/bin/g++ -g test.cpp
    # clang++ -g -Wall test.cpp
    time_check=false
else
    printf "\nCompiling in Deployment Mode...\n"
    # /usr/bin/g++ -g -Wall -static -Ofast -mavx2 -funroll-loops -fwhole-program test.cpp
    /usr/bin/g++ -g -Wall -static -Ofast -mavx2 -funroll-loops test.cpp
    time_check=true
fi

printf "Running...\n\n"

if $time_check
then
    time ./a.out
else
    ./a.out
fi
