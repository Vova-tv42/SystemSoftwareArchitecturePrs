#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Спроба прочитати /etc/shadow за допомогою sudo:\n");

    int status = system("sudo cat /etc/shadow");
    
    if (status == 0) {
        printf("\nФайл успішно прочитано.\n");
    } else {
        printf("\nНе вдалося прочитати файл. Потрібні права адміністратора.\n");
    }

    return 0;
}
