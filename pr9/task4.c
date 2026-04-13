#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Виконання команди whoami:\n");
    system("whoami");

    printf("\nВиконання команди id:\n");
    system("id");

    return 0;
}
