#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr1 = malloc(-1);
    if (ptr1 == NULL) {
        printf("malloc(-1) повернув NULL\n");
    }

    int num1 = 1024 * 1024;
    int num2 = 2048;
    int mult_res = num1 * num2;

    printf("Результат множення: %d\n", mult_res);
    void *ptr2 = malloc(mult_res);
  
    if (ptr2 == NULL) {
        printf("malloc не зміг виділити пам'ять\n");
    } else {
        printf("malloc виділив пам'ять\n");
        free(ptr2);
    }

    return 0;
}
