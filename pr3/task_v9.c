#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>

int main() {
    struct rlimit data_limit;
    
    // Встановлюємо м'який ліміт на 10 МБ, жорсткий на 20 МБ
    data_limit.rlim_cur = 10 * 1024 * 1024;
    data_limit.rlim_max = 20 * 1024 * 1024;

    if (setrlimit(RLIMIT_DATA, &data_limit) == -1) {
        printf("Помилка: не вдалося встановити обмеження RLIMIT_DATA\n");
        return 1;
    }

    printf("Виділення динамічної пам'яті (ліміт встановлено на 10 МБ)...\n");

    size_t chunk_size = 1024 * 1024; // 1 МБ
    size_t total_allocated = 0;
    
    while (1) {
        // Викликаємо malloc() для виділення 1 МБ пам'яті на heap
        char *memory_ptr = (char *) malloc(chunk_size);
        
        // Коли ліміт RLIMIT_DATA досягнуто, malloc() має повернути NULL
        if (memory_ptr == NULL) {
            printf("\nПомилка: malloc() повернув NULL. Досягнуто межі RLIMIT_DATA.\n");
            break;
        }

        // Записуємо дані у виділений блок, щоб ядро дійсно відобразило пам'ять
        memset(memory_ptr, 0, chunk_size);
        
        total_allocated += chunk_size;
        printf("Успішно виділено: %zu МБ\n", total_allocated / (1024 * 1024));
    }

    printf("\nЗагальна кількість виділеної пам'яті перед зупинкою: %zu МБ\n", 
           total_allocated / (1024 * 1024));
    printf("Завершення роботи.\n");

    return 0;
}
