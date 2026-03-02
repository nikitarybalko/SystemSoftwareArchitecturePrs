#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int condition = 2;
    
    while(condition > 0) {
        if(!ptr) {
            ptr = malloc(100);
            printf("Memory allocated: %p\n", ptr);
        }
        
        free(ptr);
        ptr = NULL; // <-- THE FIX
        
        condition--;
    }
    
    return 0;
}