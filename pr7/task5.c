#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files_recursive(const char *base_path) {
    char path[1024];
    struct dirent *entry;
    DIR *dir = opendir(base_path);

    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s/%s\n", base_path, entry->d_name);

            // Будуємо повний шлях для перевірки на підкаталог
            snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

            struct stat st;
            if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
                list_files_recursive(path);
            }
        }
    }

    closedir(dir);
}

int main() {
    printf("Список усіх файлів у поточному каталозі та підкаталогах:\n");
    list_files_recursive(".");
    return 0;
}
