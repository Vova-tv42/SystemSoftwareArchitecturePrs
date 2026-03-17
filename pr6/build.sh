#!/bin/bash

gcc -O0 task_v9.c -o task_v9_pie
gcc -O0 -no-pie task_v9.c -o task_v9_no_pie
