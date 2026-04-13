#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *pipe_input;
    char line[256];

    pipe_input = popen("getent passwd", "r");
    if (pipe_input == NULL) {
        perror("Помилка при виконанні getent");
        return 1;
    }

    printf("Звичайні користувачі в системі (UID > 1000):\n");

    while (fgets(line, sizeof(line), pipe_input)) {
        char *username = strtok(line, ":");
        strtok(NULL, ":"); // пароль
        char *uid_str = strtok(NULL, ":");
        
        if (uid_str != NULL) {
            int uid = atoi(uid_str);
            if (uid >= 1000 && strcmp(username, "nobody") != 0) {
                printf("Користувач: %s, UID: %d\n", username, uid);
            }
        }
    }

    pclose(pipe_input);
    return 0;
}
