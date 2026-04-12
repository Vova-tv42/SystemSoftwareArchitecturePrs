#include <stdio.h>
#include <stdlib.h>

void display_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Помилка при відкритті файлу");
        return;
    }

    char line[1024];
    int line_count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        line_count++;

        if (line_count == 20) {
            printf("\n--- Натисніть [Enter] для продовження ---");
            getchar();
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("=== Файл: %s ===\n", argv[i]);
        display_file(argv[i]);
    }

    return 0;
}
