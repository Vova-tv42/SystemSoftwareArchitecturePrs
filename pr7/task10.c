#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Встановлення початкового значення генератора випадкових чисел
    srand((unsigned int)time(NULL));

    // (1) Випадкове число від 0.0 до 1.0
    double rand_0_1 = (double)rand() / (double)RAND_MAX;
    printf("Випадкове число (0.0 - 1.0): %f\n", rand_0_1);

    // (2) Випадкове число від 0.0 до n
    double n = 100.0; // Значення за замовчуванням
    if (argc > 1) {
        n = atof(argv[1]);
    }

    double rand_0_n = ((double)rand() / (double)RAND_MAX) * n;
    printf("Випадкове число (0.0 - %.2f): %f\n", n, rand_0_n);

    return 0;
}
