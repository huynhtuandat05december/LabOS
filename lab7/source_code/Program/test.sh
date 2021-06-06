#!/bin/bash

rm -f mem
gcc mem.c main.c -lpthread -o mem -w
./mem

