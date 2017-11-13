#!/usr/bin/env bash

gcc -Wall -g -D_DEFAULT_SOURCE --std=c99 -Iheaders/ *.c -o debug-bibliotheque -lm

gdb debug-bibliotheque

