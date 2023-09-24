#!/usr/bin/bash

gcc -o main hash.c

./main | python count.py
