#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define PERMISSIONS S_IRUSR | S_IWUSR

int main(int argc, char *argv[]) {
    int source_fd;
    int destination_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int exit_code = EXIT_FAILURE;
    int copy_failed = 0;

    if (argc != 3) {
        fprintf(stderr, "Використання: %s <вхідний_файл> <вихідний_файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("відкриття вхідного файлу");
        return EXIT_FAILURE;
    }

    destination_fd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, PERMISSIONS);
    if (destination_fd == -1) {
        perror("відкриття вихідного файлу");
        close(source_fd);
        return EXIT_FAILURE;
    }

    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = 0;

        while (bytes_written < bytes_read) {
            ssize_t result = write(destination_fd, buffer + bytes_written,
                                   (size_t)(bytes_read - bytes_written));

            if (result == -1) {
                perror("запис");
                copy_failed = 1;
                break;
            }

            bytes_written += result;
        }

        if (copy_failed) {
            break;
        }
    }

    if (bytes_read == -1) {
        perror("читання");
    } else if (!copy_failed) {
        exit_code = EXIT_SUCCESS;
    }
    if (close(source_fd) == -1) {
        perror("закриття вхідного файлу");
        exit_code = EXIT_FAILURE;
    }

    if (close(destination_fd) == -1) {
        perror("закриття вихідного файлу");
        exit_code = EXIT_FAILURE;
    }

    return exit_code;
}
