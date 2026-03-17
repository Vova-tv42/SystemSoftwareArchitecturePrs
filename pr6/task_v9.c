#include <stdio.h>
#include <stdlib.h>

int global_variable = 42;

int main() {
    int stack_variable = 10;
    int *heap_variable = (int *) malloc(sizeof(int));

    if (heap_variable == NULL) {
        perror("Помилка виділення пам'яті");
        return 1;
    }

    printf("Адреса текстового сегменту (main): %p\n", (void *)main);
    printf("Адреса сегменту даних (global): %p\n", (void *)&global_variable);
    printf("Адреса стеку (local): %p\n", (void *)&stack_variable);
    printf("Адреса купи (heap): %p\n", (void *)heap_variable);
    printf("Адреса бібліотечної функції (printf): %p\n", (void *)printf);

    free(heap_variable);
    return 0;
}
