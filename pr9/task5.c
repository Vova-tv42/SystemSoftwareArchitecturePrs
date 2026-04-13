#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_access(const char *filename) {
    printf("\nФайл: %s\n", filename);
    
    FILE *read_file = fopen(filename, "r");
    if (read_file != NULL) {
        printf("Читання: Доступно\n");
        fclose(read_file);
    } else {
        printf("Читання: Доступ заборонено\n");
    }

    FILE *write_file = fopen(filename, "a");
    if (write_file != NULL) {
        printf("Запис: Доступно\n");
        fclose(write_file);
    } else {
        printf("Запис: Доступ заборонено\n");
    }
}

int main() {
    const char *filename = "temp_task5.txt";
    char cmd[256];

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Не вдалося створити файл");
        return 1;
    }
    fprintf(f, "Початковий вміст.\n");
    fclose(f);
    printf("Файл %s створено.\n", filename);

    snprintf(cmd, sizeof(cmd), "sudo chown root:root %s && sudo chmod 600 %s", filename, filename);
    printf("\nЗміна власника на root та прав на 600 (тільки для root)...\n");
    system(cmd);
    check_access(filename);

    snprintf(cmd, sizeof(cmd), "sudo chmod 666 %s", filename);
    printf("\nЗміна прав на 666 (доступ усім)...\n");
    system(cmd);
    check_access(filename);

    snprintf(cmd, sizeof(cmd), "sudo chmod 644 %s", filename);
    printf("\nЗміна прав на 644 (усім тільки на читання)...\n");
    system(cmd);
    check_access(filename);

    snprintf(cmd, sizeof(cmd), "sudo rm %s", filename);
    system(cmd);

    return 0;
}
