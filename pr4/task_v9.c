#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENT_SIZE 64
#define POOL_COUNT 10000

struct memory_pool {
    void *start_ptr;
    void *free_nodes[POOL_COUNT];
    int top_index;
};

void pool_init(struct memory_pool *pool) {
    pool->start_ptr = malloc(ELEMENT_SIZE * POOL_COUNT);
    pool->top_index = POOL_COUNT;
    for (int i = 0; i < POOL_COUNT; i++) {
        pool->free_nodes[i] = (char *)pool->start_ptr + (i * ELEMENT_SIZE);
    }
}

void *pool_alloc(struct memory_pool *pool) {
    if (pool->top_index <= 0) return NULL;
    return pool->free_nodes[--pool->top_index];
}

void pool_free(struct memory_pool *pool, void *ptr) {
    if (pool->top_index >= POOL_COUNT) return;
    pool->free_nodes[pool->top_index++] = ptr;
}

void pool_destroy(struct memory_pool *pool) {
    free(pool->start_ptr);
}

int main() {
    struct memory_pool pool;
    pool_init(&pool);

    clock_t start, end;
    void *ptrs[POOL_COUNT];

    // Звичайний malloc
    start = clock();
    for (int i = 0; i < POOL_COUNT; i++) {
        ptrs[i] = malloc(ELEMENT_SIZE);
    }
    
    for (int i = 0; i < POOL_COUNT; i++) {
        free(ptrs[i]);
    }
    
    end = clock();
    printf("Час роботи malloc: %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Наш memory pool
    start = clock();
    for (int i = 0; i < POOL_COUNT; i++) {
        ptrs[i] = pool_alloc(&pool);
    }

    for (int i = 0; i < POOL_COUNT; i++) {
        pool_free(&pool, ptrs[i]);
    }

    end = clock();
    printf("Час роботи Memory Pool: %f сек.\n", (double)(end - start) / CLOCKS_PER_SEC);

    pool_destroy(&pool);
    return 0;
}
