#!/usr/bin/env bash

gcc -Wall -g -D_DEFAULT_SOURCE --std=c99 -Iheaders/ *.c -o debug-bibliotheque

gdb debug-bibliotheque

