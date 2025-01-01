#!/bin/bash
NUM_CORES=$(nproc)
echo "Number of cores detected: $NUM_CORES"
cmake -S . -B ./build && cmake --build ./build -j $NUM_CORES
