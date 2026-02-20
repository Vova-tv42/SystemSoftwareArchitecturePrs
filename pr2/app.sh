#!/bin/bash

echo "--- Варіант 9: BSS vs Data ---"
gcc -DUSE_BSS segments_investigation.c -o program_bss
gcc segments_investigation.c -o program_default
ls -l program_bss program_default 
size program_bss program_default 
echo "BSS менший на диску, бо зберігає лише розмір, а звичайна програма - всі значення."

gcc memory.c -o memory
./memory
