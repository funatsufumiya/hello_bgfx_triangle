#!/bin/bash

NAME=$1

if [ -z "$NAME" ]; then
    NAME="triangle"
fi

# if only exists, then run
exe=./build/triangle/big2_example_${NAME}
if [ -f "$exe" ]; then
    echo "Running $NAME example"
    $exe
else
    echo "Example $NAME does not exist"
    exit 1
fi
