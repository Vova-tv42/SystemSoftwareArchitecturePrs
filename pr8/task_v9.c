#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int n = 3; // Кількість ітерацій

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork() не вдався");
            return 1;
        }

        if (pid == 0) {
            printf("Ітерація %d: Дочірній процес (PID: %d, PPID: %d)\n", i, getpid(), getppid());
        } else {
            printf("Ітерація %d: Батьківський процес (PID: %d) створив дочірній (PID: %d)\n", i, getpid(), pid);
        }

        sleep(1);
    }

    sleep(1);
    return 0;
}
