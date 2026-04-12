#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *directory;
    struct dirent *entry;
    struct stat file_info;
    struct passwd *user_info;
    struct group *group_info;
    char time_buffer[26];

    directory = opendir(".");
    if (directory == NULL) {
        perror("Помилка при відкритті каталогу");
        return 1;
    }

    while ((entry = readdir(directory)) != NULL) {
        if (stat(entry->d_name, &file_info) == -1) {
            continue;
        }

        print_permissions(file_info.st_mode);
        printf(" %2ld", (long)file_info.st_nlink);

        user_info = getpwuid(file_info.st_uid);
        group_info = getgrgid(file_info.st_gid);

        printf(" %-8s %-8s", (user_info ? user_info->pw_name : "???"), (group_info ? group_info->gr_name : "???"));
        printf(" %8lld", (long long)file_info.st_size);

        strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", localtime(&file_info.st_mtime));
        printf(" %s %s\n", time_buffer, entry->d_name);
    }

    closedir(directory);
    return 0;
}
