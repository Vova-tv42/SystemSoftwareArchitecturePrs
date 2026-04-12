#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка при відкритті каталогу");
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    char response;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Перевіряємо, чи це файл
        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            printf("Видалити файл '%s'? (y/n): ", entry->d_name);
            scanf(" %c", &response);

            if (response == 'y' || response == 'Y') {
                if (unlink(entry->d_name) == 0) {
                    printf("Файл видалено.\n");
                } else {
                    perror("Помилка при видаленні файлу");
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
