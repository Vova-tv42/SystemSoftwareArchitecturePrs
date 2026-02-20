#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int initialized_global = 1;
int uninitialized_global;

void investigate_stack_growth(int recursion_depth) {
    int local_stack_var;
    printf("Стек рівень %d: %p\n", recursion_depth, (void*)&local_stack_var);
   
    if (recursion_depth < 5) {
        investigate_stack_growth(recursion_depth + 1);
    }
}

int main() {
    printf("\n--- Аналіз проблеми 2038 (симуляція 32-біт) ---\n");
    int32_t t32_max = 0x7FFFFFFF;
    int32_t t32_overflow = t32_max + 1;

    // Конвертуємо у тип time_t (для коректного виводу даних)
    time_t time_before = (time_t)t32_max;
    time_t time_after = (time_t)t32_overflow;

    printf("Час до переповнення (32-біт): %s", ctime(&time_before));
    printf("Час після переповнення (32-біт): %s", ctime(&time_after));

    printf("\nАдреси:\n");
    int local_var;
    int *heap_pointer = malloc(4);
    printf("Text:  %p\n", (void*)main);
    printf("Data:  %p\n", (void*)&initialized_global);
    printf("BSS:   %p\n", (void*)&uninitialized_global);
    printf("Heap:  %p\n", (void*)heap_pointer);
    printf("Stack: %p\n", (void*)&local_var);

    printf("\nРіст стеку:\n");
    investigate_stack_growth(1);

    free(heap_pointer);
    return 0;
}
