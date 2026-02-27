#!/bin/bash

# Завдання 3.2: Використання perf у Docker
echo "--- Експеримент 3.2: perf ---"

echo "[1] Запуск perf stat для ./task4"
perf stat ./task4 || echo "Помилка: perf заблоковано ядром. Запустіть Docker з флажком --privileged."

echo "[2] Перегляд доступних системних подій (perf list):"
perf list | head -n 20
