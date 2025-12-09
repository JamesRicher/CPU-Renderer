#!/bin/zsh

cmake -B build -S . --preset default
cmake --build build
