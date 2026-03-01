#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = realloc(NULL, 100);
    if (ptr) {
        printf("realloc(NULL, 100) спрацював як malloc. Адреса: %p\n", ptr);
    }

    void *result = realloc(ptr, 0);
    printf("realloc(ptr, 0) Звільнив пам'ять. Результат: %p\n", result);

    return 0;
}
