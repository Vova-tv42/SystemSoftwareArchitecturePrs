#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

void handle_copy_limit(int sig) {
    printf("\n[СИГНАЛ] Ліміт розміру файлу досягнуто під час копіювання.\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Програма приймає 2 аргументи\n");
        return 1;
    }

    const char *source_filename = argv[1];
    const char *dest_filename = argv[2];

    FILE *source_file = fopen(source_filename, "r");
    if (source_file == NULL) {
        printf("Не вийшло відкрити файл \"%s\" для читання\n", source_filename);
        return 1;
    }

    FILE *dest_file = fopen(dest_filename, "w");
    if (dest_file == NULL) {
        printf("Не вийшло відкрити файл \"%s\" для написання\n", dest_filename);
        fclose(source_file);
        return 1;
    }

    struct rlimit copy_limit;
    copy_limit.rlim_cur = 1024;
    copy_limit.rlim_max = 1024;

    if (setrlimit(RLIMIT_FSIZE, &copy_limit) == -1) {
        printf("Помилка: не вдалося встановити обмеження RLIMIT_FSIZE\n");
        fclose(source_file);
        fclose(dest_file);
        return 1;
    }

    // Реєструємо обробник сигналу
    signal(SIGXFSZ, handle_copy_limit);
    printf("Копіювання %s до %s (ліміт 1 КБ)...\n", source_filename, dest_filename);

    char buffer[256];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), source_file);
    
    while (bytes_read > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
        
        if (bytes_written < bytes_read) {
            // Якщо записано менше ніж прочитано (наприклад, через ліміт)
            break; 
        }
        
        // Оновлюємо кількість прочитаних байт для наступної ітерації
        bytes_read = fread(buffer, 1, sizeof(buffer), source_file);
    }

    printf("Копіювання завершено.\n");
    fclose(source_file);
    fclose(dest_file);
    return 0;
}
