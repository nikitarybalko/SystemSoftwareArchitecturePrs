#include <stdio.h>
#include <stdlib.h>

void recursive_function(int depth) {
    char stack_eater[10240];
    
    if (depth % 100 == 0) {
        printf("Recursion depth: %d (Approx %d KB used)\n", depth, depth * 10);
        fflush(stdout); 
    }

    stack_eater[0] = 'A';

    recursive_function(depth + 1);
}

int main() {
    printf("Starting stack overflow demonstration...\n");
    printf("Watch the depth counter until the OS kills the process.\n\n");
    
    recursive_function(1);
    
    return 0;
}