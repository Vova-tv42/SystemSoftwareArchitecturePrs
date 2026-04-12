#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int main() {
    int pipe_fd[2];
    ssize_t written_bytes;

    // Ігноруємо SIGPIPE, щоб write повернув -1 замість завершення програми
    signal(SIGPIPE, SIG_IGN);

    if (pipe(pipe_fd) == -1) {
        perror("Помилка створення каналу");
        return 1;
    }

    // Закриваємо сторону для читання
    close(pipe_fd[0]);

    const char *data = "Привіт, світ!";
    size_t length = strlen(data);

    // Спроба запису в канал без читача
    written_bytes = write(pipe_fd[1], data, length);

    if (written_bytes != (ssize_t)length) {
        printf("Записано байтів: %ld, очікувалось: %zu\n", written_bytes, length);
        if (written_bytes == -1) {
            printf("Помилка (errno %d): %s\n", errno, strerror(errno));
        }
    }

    close(pipe_fd[1]);
    return 0;
}
