#include <stdio.h>
#include <stdlib.h>

void* shared_resource = NULL;

void first_cleanup_handler() {
    printf("Перша гілка логіки звільняє пам'ять\n");
    free(shared_resource);
}

void second_cleanup_handler() {
    printf("Друга гілка логіки звільняє пам'ять\n");
    free(shared_resource);
}

int main() {
    shared_resource = malloc(1024);
    if (shared_resource == NULL) {
        printf("Помилка виділення пам'яті\n");
        return 1;
    }

    printf("Пам'ять виділена за адресою: %p\n", shared_resource);

    // Імітуємо послідовність викликів, яка призводить до помилки
    first_cleanup_handler();
    
    printf("Викликаємо другу гілку очищення\n");
    second_cleanup_handler(); // Тут виникне Double Free

    printf("Програма завершена\n");
    return 0;
}
