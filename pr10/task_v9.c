#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t children[10];
    int i;

    printf("Батьківський процес (PID: %d) створює 10 дочірніх процесів\n", getpid());

    for (i = 0; i < 10; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Помилка fork");
            exit(1);
        } else if (pid == 0) {
            printf("Дочірній процес %d (PID: %d) запущено\n", i + 1, getpid());
            sleep(1);
            exit(0);
        } else {
            children[i] = pid;
        }
    }

    printf("\nБатьківський процес чекає на завершення дочірніх процесів\n");

    for (i = 0; i < 10; i++) {
        int status;
        pid_t finished_pid = waitpid(children[i], &status, 0);
        if (finished_pid > 0) {
            printf("Дочірній процес з PID %d завершився\n", finished_pid);
        }
    }

    printf("\nУсі дочірні процеси завершені. Батьківський процес завершує роботу.\n");

    return 0;
}
