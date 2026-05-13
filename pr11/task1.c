#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

void get_process_name(pid_t pid, char *name, size_t len) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    int fd = open(path, O_RDONLY);
    if (fd != -1) {
        ssize_t bytes = read(fd, name, len - 1);
        if (bytes > 0) {
            name[bytes - 1] = '\0';
        }
        close(fd);
    } else {
        strncpy(name, "невідомо", len);
    }
}


void signal_handler(int sig, siginfo_t *info, void *context) {
    char process_name[256];
    get_process_name(info->si_pid, process_name, sizeof(process_name));

    FILE *log_file = fopen("/tmp/signals.log", "a");
    if (log_file) {
        fprintf(log_file, "Сигнал: %d | Відправник PID: %d | UID: %d | GID: %d | Процес: %s\n",
                sig, info->si_pid, info->si_uid, getgid(), process_name);
        fclose(log_file);
    }
}

void create_daemon() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    if (setsid() < 0) exit(EXIT_FAILURE);

    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0);
    chdir("/");

    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x);
    }
}

int main() {
    create_daemon();

    struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    for (int i = 1; i < 32; i++) {
        if (i != SIGKILL && i != SIGSTOP && i != SIGCHLD) {
            sigaction(i, &sa, NULL);
        }
    }

    while (1) {
        pause();
    }

    return 0;
}
