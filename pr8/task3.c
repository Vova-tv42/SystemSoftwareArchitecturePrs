#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparison_count = 0;

int compare(const void *a, const void *b) {
    comparison_count++;
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;

    return 0;
}

void fill_random(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
}

void fill_sorted(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

void fill_reversed(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void test_array(int size, void (*fill_func)(int[], int), const char *label) {
    int *arr = malloc(size * sizeof(int));
    fill_func(arr, size);
   
    comparison_count = 0;
    qsort(arr, size, sizeof(int), compare);
    printf("%s: %d порівнянь\n", label, comparison_count);
    
    free(arr);
}

int main() {
    srand(time(NULL));
    int size = 1000;

    printf("Розмір масиву: %d\n", size);
    test_array(size, fill_random, "Випадковий масив");
    test_array(size, fill_sorted, "Відсортований масив");
    test_array(size, fill_reversed, "Зворотньо відсортований масив");

    return 0;
}
