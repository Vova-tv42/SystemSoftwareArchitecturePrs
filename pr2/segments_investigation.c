#include <stdio.h>

#ifdef USE_BSS
int big_array[1000000];
#else
int big_array[1000000] = {1};
#endif

int main() {
    printf("Адреса масиву: %p\n", big_array);
    return 0;
}
