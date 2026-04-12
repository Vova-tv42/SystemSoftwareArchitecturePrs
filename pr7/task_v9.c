#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s <IP-адреса>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int start_port = 20;
    int end_port = 100; // Для прикладу скануємо невеликий діапазон

    printf("Сканування портів на %s від %d до %d...\n", ip, start_port, end_port);

    for (int port = start_port; port <= end_port; port++) {
        char command[256];
        // Використовуємо nc -z (zero-I/O mode) для перевірки з'єднання
        // -w 1 задає таймаут в 1 секунду
        snprintf(command, sizeof(command), "nc -z -w 1 %s %d 2>&1", ip, port);

        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            perror("Помилка при виконанні popen");
            continue;
        }

        // В деяких версіях nc результат виводиться в stderr, тому ми його перенаправили
        // Але найпростіше перевірити статус завершення через pclose
        int status = pclose(fp);

        if (status == 0) {
            printf("Порт %d [ВІДКРИТИЙ]\n", port);
        }
    }

    return 0;
}
