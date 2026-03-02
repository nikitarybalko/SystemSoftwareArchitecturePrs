#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_memory_maps(const char *label) {
    char cmd[256];
    printf("\n--- %s ---\n", label);
    snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps | grep -E 'heap|^[0-9a-f].* 00000000 00:00 0 '", getpid());
    system(cmd);
}

int main() {
    int num_small_blocks = 200000;
    
    print_memory_maps("Memory map before allocation");

    size_t large_size = 200 * 1024 * 1024;
    void *large_block = malloc(large_size);
    print_memory_maps("After malloc(200 MB) - pay attention to the new big anonymous segment");

    void **small_blocks = malloc(200000 * sizeof(void*));
    for (int i = 0; i < 200000; i++) {
        small_blocks[i] = malloc(1024);
    }
    print_memory_maps("After 200 000 * 1 KB - pay attention to the increase in size [heap]");

    // freeing the memory

    free(large_block);
    
    for (int i = 0; i < num_small_blocks; i++) {
        free(small_blocks[i]);
    }
    
    free(small_blocks);

    print_memory_maps("Memory freed");
    
    return 0;
}