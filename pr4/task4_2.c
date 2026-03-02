#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 100000;
    int xb = 30000;
    
    int num = xa * xb; 
    printf("Multiplication result (signed int): %d\n", num);
    
    printf("Attempt of malloc(%d) (%zu in size_t):\n", num, (size_t)num);
    void *ptr = malloc(num);
    
    if(ptr == NULL) {
        printf("Allocation error.\n");
    } else {
        free(ptr);
    }
    
    return 0;
}