#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];
    
    fd = open("temp_data.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    write(fd, data, sizeof(data));

    // Переміщуємо покажчик на 3-й байт (індекс 3)
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("Помилка lseek");
        close(fd);
        return 1;
    }

    // Зчитуємо 4 байти
    ssize_t bytes_read = read(fd, buffer, 4);
    if (bytes_read == -1) {
        perror("Помилка читання");
        close(fd);
        return 1;
    }

    printf("Зчитано %ld байтів: ", bytes_read);
    for (int i = 0; i < bytes_read; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    unlink("temp_data.bin");
    return 0;
}
