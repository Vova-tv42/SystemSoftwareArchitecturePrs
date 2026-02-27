#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <time.h>

// Обробник сигналу перевищення розміру файлу
void handle_file_size_limit(int sig) {
    printf("\n[СИГНАЛ] Досягнуто ліміту розміру файлу (SIGXFSZ). Завершення...\n");
    exit(0);
}

int main() {
    struct rlimit limit;
    
    // Встановлюємо ліміт на 2048 байт (2 КБ)
    limit.rlim_cur = 2048; 
    limit.rlim_max = 2048;

    if (setrlimit(RLIMIT_FSIZE, &limit) == -1) {
        printf("Помилка: не вдалося встановити обмеження RLIMIT_FSIZE\n");
        return 1;
    }

    // Реєструємо обробник сигналу
    signal(SIGXFSZ, handle_file_size_limit);
    srand(time(NULL));
    
    FILE *output_file = fopen("dice_rolls.txt", "w");
    if (output_file == NULL) {
        printf("Помилка: не вдалося відкрити файл для запису\n");
        return 1;
    }

    printf("Початок запису результатів у dice_rolls.txt (ліміт 2 КБ)...\n");

    while (1) {
        int dice_value = (rand() % 6) + 1;
        fprintf(output_file, "%d\n", dice_value);
    }

    fclose(output_file);
    return 0;
}
