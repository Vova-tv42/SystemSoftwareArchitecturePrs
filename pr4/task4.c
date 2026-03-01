#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- Демонстрація помилкового коду ---\n");
    void *ptr = NULL;
    int repeat_count = 3;

    while (repeat_count--) {
        if (!ptr) {
            ptr = malloc(100);
            printf("Виділено нову пам'ять: %p\n", ptr);
        } else {
            printf("Помилка: використовується стара адреса %p\n", ptr);
        }
        
        free(ptr);
    }

    return 0;
}
