#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("=== Вивід whoami ===\n");
    system("whoami");

    printf("\n=== Вивід id ===\n");
    system("id");

    return 0;
}