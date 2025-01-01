#!/bin/bash
if [ -z "$NUM_CORES" ]; then
    if [ -x "$(command -v nproc)" ]; then
        NUM_CORES=$(nproc)
        echo "Number of cores detected: $NUM_CORES"
    elif [ -x "$(command -v sysctl)" ]; then
        NUM_CORES=$(sysctl -n hw.logicalcpu)
        echo "Number of cores detected: $NUM_CORES"
    else
        NUM_CORES=4
        echo "Number of cores not detected, using default value: $NUM_CORES"
    fi
else
    echo "Number of cores set by user env: $NUM_CORES"
fi
cmake --build ./build -j $NUM_CORES
