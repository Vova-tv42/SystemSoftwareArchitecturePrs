#!/bin/bash

gcc -g task_v9.c -o task_v9
echo "Щоб перевірити за допомогою Valgrind: valgrind --leak-check=full ./task_v9"
