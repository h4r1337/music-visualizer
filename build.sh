#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra `pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` -lm -ldl -lpthread"

clang $CFLAGS -o ./bin/visualizer main.c $LIBS
