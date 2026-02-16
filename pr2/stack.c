#include <stdio.h>
#include <stdlib.h>

int global_initialized = 42;

int global_uninit;

void stack_growth_test() {
    int big_array_1[1000]; 
    int big_array_2[1000];
    
    int stack_var_inner;

    printf("\n[FUNCTION CALL]\n");
    printf("Big arrays allocated...\n");
    printf("TOS address inside function: %p\n", (void*)&stack_var_inner);
}

int main() {
    printf("main function address (Text Segment):      %p\n", (void*)main);

    printf("Data Segment address (global_init):       %p\n", (void*)&global_initialized);
    printf("BSS Segment address (global_uninit):      %p\n", (void*)&global_uninit);

    int *heap_var = (int*)malloc(sizeof(int));
    if (heap_var == NULL) {
        perror("malloc failed");
        return 1;
    }
    printf("Heap address:         %p\n", (void*)heap_var);

    int stack_var_main;
    printf("Stack address (in main):                   %p\n", (void*)&stack_var_main);

    stack_growth_test();

    return 0;
}