#!/bin/zsh

set -e

./build.sh

echo "Build success, running program..."
./build/CPURenderer
