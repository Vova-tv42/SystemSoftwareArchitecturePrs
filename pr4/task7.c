#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int data[10];
};

int main() {
    struct sbar *ptr, *new_ptr;

    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        printf("Не вийшло виділити пам'ять");
        return 1;
    }
    printf("Виділено пам'ять для 1000 елементів.\n");
 
    new_ptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (new_ptr) {
        printf("reallocarray успішно змінив розмір\n");
        free(new_ptr);
    } else {
        printf("Помилка reallocarray\n");
        free(ptr);
    }

    return 0;
}
