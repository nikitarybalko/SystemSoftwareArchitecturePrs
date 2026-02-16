#include <stdio.h>

int calculate(int a, int b) {
    return (a * b) + (a - b);
}

int main() {
    int sum = 0;
    
    for (int i = 0; i < 1000; i++) {
        sum += calculate(i, i + 1);
    }
    
    printf("Result: %d\n", sum);
    return 0;
}