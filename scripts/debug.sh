#!/bin/bash

gcc -O0 -g -Wall ../serial_aes.c ../serial_main.c -o ../bin/serial_aes -lm
cd .. && ./bin/serial_aes