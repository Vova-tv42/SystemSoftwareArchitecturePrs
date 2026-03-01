#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = (size_t)-1;
    void *ptr = malloc(max_size);

    if (ptr == NULL) {
        printf("Не вдалося виділити %zu байтів. Це занадто багато.\n", max_size);
    } else {
        printf("Пам'ять виділено.\n");
        free(ptr);
    }

    return 0;
}
