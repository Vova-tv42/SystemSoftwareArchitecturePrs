#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 1000

typedef struct {
    char username[64];
    int uid;
} UserInfo;

int main() {
    FILE *f = fopen("/etc/passwd", "r");
    if (f == NULL) {
        perror("Не вдалося відкрити /etc/passwd");
        return 1;
    }

    UserInfo users[MAX_USERS];
    int user_count = 0;
    char line[256];

    while (fgets(line, sizeof(line), f) && user_count < MAX_USERS) {
        char *name = strtok(line, ":");
        strtok(NULL, ":"); // пароль
        char *uid_str = strtok(NULL, ":");
        
        if (name && uid_str) {
            strncpy(users[user_count].username, name, 63);
            users[user_count].uid = atoi(uid_str);
            user_count++;
        }
    }
    fclose(f);

    printf("Перевірка на наявність однакових UID у системі...\n");
    int duplicates_found = 0;

    for (int i = 0; i < user_count; i++) {
        for (int j = i + 1; j < user_count; j++) {
            if (users[i].uid == users[j].uid) {
                printf("Знайдено дублікат UID %d: користувачі '%s' та '%s'\n", 
                       users[i].uid, users[i].username, users[j].username);
                duplicates_found = 1;
            }
        }
    }

    if (!duplicates_found) {
        printf("Дублікатів UID не знайдено.\n");
    }

    printf("\n--- Пояснення ---\n");
    printf("У Linux можна мати два різні облікові записи з однаковим UID.\n");
    printf("Наслідки:\n");
    printf("1. Система вважатиме їх одним і тим самим користувачем.\n");
    printf("2. Вони матимуть однакові права доступу до файлів.\n");
    printf("3. Команда 'whoami' поверне ім'я того користувача, який іде першим у /etc/passwd.\n");
    printf("4. Це може створювати серйозні проблеми з безпекою та плутанину при логуванні дій.\n");

    return 0;
}
