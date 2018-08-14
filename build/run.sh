#!/bin/bash

cmake ..
make
./simorgh > out.temp
cat out.temp
wc < out.temp
rm out.temp
