#include <stdio.h>
#include <sys/resource.h>

// Рекурсивна функція для демонстрації переповнення стеку
void demonstrate_recursion(int current_depth) {
    // Великий локальний масив для швидшого переповнення стеку
    char buffer[1024 * 64]; // 64 КБ
    
    // Виводимо з кроком в 10 викликів
    if (current_depth % 10 == 0) {
        printf(
            "Поточна глибина рекурсії: %d (використано %d КБ)\n", 
            current_depth, current_depth * 64
        );
    }
    
    // Записуємо дані у буфер, щоб він був реально виділений
    buffer[0] = 1;
    demonstrate_recursion(current_depth + 1);
}

int main() {
    struct rlimit stack_limit;
    
    // Отримуємо поточний ліміт стеку за допомогою getrlimit
    if (getrlimit(RLIMIT_STACK, &stack_limit) == -1) {
        printf("Помилка: не вдалося отримати RLIMIT_STACK\n");
        return 1;
    }

    printf("М'який ліміт стеку: %ld байт (%ld КБ)\n", 
           (long)stack_limit.rlim_cur, (long)stack_limit.rlim_cur / 1024);
    
    printf("Початок рекурсії (очікуємо 'Segmentation fault' при досягненні межі)...\n");

    // Запускаємо нескінченну рекурсію
    demonstrate_recursion(1);
    return 0;
}
