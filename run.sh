#!/bin/bash

NAME=$1

if [ -z "$NAME" ]; then
    NAME="basic"
fi

./build/triangle/big2_example_${NAME}