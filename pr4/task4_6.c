#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = realloc(NULL, 1024);
    printf("realloc(NULL, 1024) returned: %p (equivalent of malloc)\n", ptr);
    

    void *new_ptr = realloc(ptr, 0);
    printf("realloc(ptr, 0) returned: %p (equivalent of free)\n", new_ptr);
    
    return 0;
}