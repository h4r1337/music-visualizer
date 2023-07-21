#!/bin/bash

set -xe

CFLAGS="-Wall -Wextra"

clang $CFLAGS -o ./bin/visualizer main.c
