#!/bin/bash

cmake -DCMAKE_BUILD_TYPE=Debug ..
make
gdb ./simorgh
