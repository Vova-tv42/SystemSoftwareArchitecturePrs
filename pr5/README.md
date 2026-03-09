# Практична робота №5: Про помилки роботи з пам’яттю в Linux та засоби їх усунення

## Складання та запуск

Для компіляції завдання використовується скрипт `build.sh`.

**Команда для компіляції:**
```bash
./build.sh
```

---

## task_v9.c
Програма моделює ситуацію виникнення помилки подвійного звільнення пам'яті (`double free`). Помилка виникає через те, що вказівник на спільний ресурс (`shared_resource`) не занулюється після першого звільнення пам'яті у функції `first_cleanup_handler`, що призводить до повторної спроби звільнення тієї ж адреси у функції `second_cleanup_handler`.

**Результат виконання без valgrind:**

<img width="445" height="183" alt="image" src="https://github.com/user-attachments/assets/dee3e37f-ca45-47ae-b1c7-d374ae209207" />

**Результат виконання з valgrind:**

<img width="953" height="736" alt="image" src="https://github.com/user-attachments/assets/7a3a913c-c348-44b8-a883-6dfe81dfea18" />
