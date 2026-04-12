#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Використання: %s <слово> <файл>\n", argv[0]);
        return 1;
    }

    char *target_word = argv[1];
    char *file_name = argv[2];
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        perror("Помилка при відкритті файлу");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, target_word) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
