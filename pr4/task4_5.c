#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    void *original_ptr = malloc(1024);
    printf("Original block: %p\n", original_ptr);
    
    void *temp = realloc(original_ptr, SIZE_MAX); 
    
    if(temp == NULL) {
        printf("realloc returned NULL. But original block is still valid: %p\n", original_ptr);
        free(original_ptr);
    } else {
        free(temp);
    }
    
    return 0;
}