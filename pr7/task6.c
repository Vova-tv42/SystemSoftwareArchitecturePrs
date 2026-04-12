#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int filter_subdirectories(const struct dirent *entry) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        return 0;
    }

    struct stat st;
    if (stat(entry->d_name, &st) == 0) {
        return S_ISDIR(st.st_mode);
    }
    return 0;
}

int main() {
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, filter_subdirectories, alphasort);
    if (n < 0) {
        perror("Помилка при скануванні каталогу");
        return 1;
    }

    printf("Список підкаталогів у алфавітному порядку:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", namelist[i]->d_name);
        free(namelist[i]);
    }
    free(namelist);

    return 0;
}
