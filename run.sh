#!/bin/bash

NAME=$1

if [ -z "$NAME" ]; then
    NAME="triangle"
fi

./build/triangle/big2_example_${NAME}
