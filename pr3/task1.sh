#!/bin/bash

# Завдання 3.1: Експерименти з лімітом відкритих файлів у Docker
echo "--- Завдання 3.1: ulimit -n ---"

echo "[1] Перегляд поточного ліміту:"
ulimit -n

echo "[2] Перегляд м'якого ліміту (Soft Limit):"
ulimit -aS | grep "open files"

echo "[3] Перегляд жорсткого ліміту (Hard Limit):"
ulimit -aH | grep "open files"

echo "[4] Спроба встановити ліміт 3000:"
ulimit -n 3000

echo "[5] Перевірка результату після зміни:"
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"

echo "[6] Спроба встановити ліміт 3001:"
ulimit -n 3001 || echo "Помилка: тільки root може підняти жорсткий ліміт."

echo "[7] Спроба встановити ліміт 2000:"
ulimit -n 2000

echo "[8] Перегляд поточного ліміту:"
ulimit -n

echo "[9] Перегляд м'якого та жорсткого лімітів:"
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"

echo "[10] Повернення до 3000:"
ulimit -n 3000 || echo "Помилка: тільки root може підняти жорсткий ліміт."
