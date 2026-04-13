#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "user_test_file.txt";
    const char *home_path = getenv("HOME");
    char root_file_path[512];

    if (home_path == NULL) {
        printf("Помилка: неможливо визначити домашню директорію.\n");
        return 1;
    }

    snprintf(root_file_path, sizeof(root_file_path), "%s/root_copy.txt", home_path);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fprintf(file, "Це файл, створений звичайним користувачем.\n");
    fclose(file);
    printf("Файл %s створено.\n", filename);

    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "sudo cp %s %s && sudo chown root:root %s", filename, root_file_path, root_file_path);
    printf("Копіюємо файл від імені root у %s...\n", root_file_path);
    system(cmd);

    printf("\nСпроба змінити файл (редагування)...\n");
    FILE *root_file = fopen(root_file_path, "a");
    if (root_file == NULL) {
        printf("Результат: Доступ заборонено (власник root).\n");
    } else {
        fprintf(root_file, "Новий рядок від користувача.\n");
        fclose(root_file);
        printf("Результат: Файл змінено успішно.\n");
    }
// 4. Спроба видалити файл за допомогою rm
printf("\nБажаєте спробувати видалити цей файл? (y/n): ");
char choice;
scanf(" %c", &choice);

if (choice == 'y' || choice == 'Y') {
    printf("Спроба видалити файл командою rm...\n");
    snprintf(cmd, sizeof(cmd), "rm -f %s", root_file_path);
    int rm_status = system(cmd);
    if (rm_status == 0) {
        printf("Результат: Файл успішно видалено (користувач може видаляти файли у своїй директорії, навіть якщо вони йому не належать).\n");
    } else {
        printf("Результат: Помилка при видаленні.\n");
    }
} else {
    printf("Видалення скасовано користувачем.\n");
}


    return 0;
}
