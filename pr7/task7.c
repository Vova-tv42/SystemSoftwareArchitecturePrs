#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

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
        // Перевіряємо, чи це файл .c
        size_t len = strlen(entry->d_name);
        if (len > 2 && strcmp(entry->d_name + len - 2, ".c") == 0) {
            printf("Файл: %s\n", entry->d_name);
            printf("Надати дозвіл на читання для інших? (y/n): ");
            scanf(" %c", &response);

            if (response != 'y' && response !='Y') continue;
            if (stat(entry->d_name, &st) != 0) continue;
         
            if (chmod(entry->d_name, st.st_mode | S_IROTH) != 0) {
                perror("Помилка при зміні прав доступу");
                continue;
            } 

            printf("Дозвіл надано.\n");
        }
    }

    closedir(dir);
    return 0;
}
