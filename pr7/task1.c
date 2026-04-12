#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *read_ptr;
    FILE *write_ptr;
    char buffer[1024];

    read_ptr = popen("who", "r");
    if (read_ptr == NULL) {
        perror("Помилка при виконанні rwho");
        return 1;
    }

    write_ptr = popen("more", "w");
    if (write_ptr == NULL) {
        perror("Помилка при виконанні more");
        pclose(read_ptr);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), read_ptr) != NULL) {
        fputs(buffer, write_ptr);
    }

    pclose(read_ptr);
    pclose(write_ptr);

    return 0;
}
