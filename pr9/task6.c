#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Перегляд прав доступу до домашнього каталогу, /usr/bin та /etc:\n");
    system("ls -ld ~ /usr/bin /etc");

    printf("\n--- Спроба обійти права доступу ---\n");

    printf("\n1. Спроба читання /etc/shadow (власник root, доступ обмежено):\n");
    FILE *f_shadow = fopen("/etc/shadow", "r");
    if (f_shadow == NULL) {
        printf("Результат: Читання заборонено (Permission denied).\n");
    } else {
        printf("Результат: Неочікуваний успіх при читанні.\n");
        fclose(f_shadow);
    }

    printf("\n2. Спроба запису у /etc/passwd (власник root, зазвичай тільки для читання):\n");
    FILE *f_passwd = fopen("/etc/passwd", "a");
    if (f_passwd == NULL) {
        printf("Результат: Запис заборонено (Permission denied).\n");
    } else {
        printf("Результат: Неочікуваний успіх при записі.\n");
        fclose(f_passwd);
    }

    printf("\n3. Спроба виконання файлу без прав виконання (наприклад, /etc/hosts):\n");
    int exec_status = system("/etc/hosts");
    if (exec_status != 0) {
        printf("Результат: Виконання заборонено або неможливе (Permission denied).\n");
    } else {
        printf("Результат: Виконання успішне (неочікувано).\n");
    }

    return 0;
}
