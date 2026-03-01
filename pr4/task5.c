#include <stdio.h>
#include <stdlib.h>

int main() {
    void *initial_ptr = malloc(100);
    if (!initial_ptr) {
        printf("Не вийшло виділити пам'ять з malloc\n");
        return 1;
    }

    printf("Початкова адреса: %p\n", initial_ptr);
    void *new_ptr = realloc(initial_ptr, (size_t) -1);

    if (new_ptr == NULL) {
        printf("realloc не зміг виділити пам'ять. Оригінальна адреса %p все ще дійсна\n", initial_ptr);
        free(initial_ptr);
    } else {
        printf("realloc успішно змінив розмір\n");
        free(new_ptr);
    }

    return 0;
}
