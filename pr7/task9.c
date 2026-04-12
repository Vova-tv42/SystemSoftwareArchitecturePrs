#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void code_to_measure() {
    long long sum = 0;
    for (int i = 0; i < 100000000; i++) {
        sum += i;
    }
    printf("Результат обчислень: %lld\n", sum);
}

int main() {
    struct timespec start, end;

    // Отримуємо початковий час
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror("clock_gettime");
        return 1;
    }

    code_to_measure();

    // Отримуємо кінцевий час
    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
        perror("clock_gettime");
        return 1;
    }

    // Розрахунок часу в мілісекундах
    double start_ms = (double)start.tv_sec * 1000.0 + (double)start.tv_nsec / 1000000.0;
    double end_ms = (double)end.tv_sec * 1000.0 + (double)end.tv_nsec / 1000000.0;
    double elapsed_ms = end_ms - start_ms;

    printf("Час виконання фрагмента коду: %.3f мс\n", elapsed_ms);

    return 0;
}
