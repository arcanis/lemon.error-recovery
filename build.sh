#!/usr/bin/env bash
lemon test.lm
rm test.out
g++ -std=c++11 test.cc
