#include <stdio.h>

int replace(char *str, char replacement);

int main(int argc, char *argv[]) {
    char default_str[] = "The cat sat";
    char *input_str = default_str;
    char replacement = '-';

    if (argc > 1) {
        input_str = argv[1];
    }

    if (argc > 2) {
        replacement = argv[2][0];
    }

    int count = replace(input_str, replacement);
    printf("Output: \"%s\", Replaced: %d\n", input_str, count);

    return 0;
}

int replace(char *str, char replacement) {
    if (str == NULL) return 0;

    int count = 0;
    while (*str) {
        if (*str == ' ') {
            *str = replacement;
            count++;
        }
     
	str++;
    }

    return count;
}
