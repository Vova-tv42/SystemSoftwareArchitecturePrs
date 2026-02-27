#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <time.h>

// Обробник сигналу перевищення часу ЦП
void handle_cpu_time_limit(int sig) {
    printf("\n[СИГНАЛ] Ліміт часу процесора вичерпано (SIGXCPU). Завершення...\n");
    exit(0);
}

// Функція для генерації та виводу комбінації лотереї
void print_lottery_combination(int count, int max_number) {
    printf("Лотерея (%d із %d): ", count, max_number);
    for (int i = 0; i < count; i++) {
        int random_num = (rand() % max_number) + 1;
        printf("%d ", random_num);
    }
   
    printf("\n");
}

int main() {
    struct rlimit cpu_limit;
    
    // Встановлюємо м'який ліміт на 1 секунду, жорсткий на 2 секунди
    cpu_limit.rlim_cur = 1; 
    cpu_limit.rlim_max = 2;

    if (setrlimit(RLIMIT_CPU, &cpu_limit) == -1) {
        printf("Помилка: не вдалося встановити обмеження RLIMIT_CPU\n");
        return 1;
    }

    // Реєструємо обробник сигналу
    signal(SIGXCPU, handle_cpu_time_limit);
    srand(time(NULL));

    printf("Початок генерації комбінацій (ліміт часу ЦП 1 секунда)...\n");

    while (1) {
        print_lottery_combination(7, 49);
        print_lottery_combination(6, 36);
        printf("---\n");
    }

    return 0;
}
