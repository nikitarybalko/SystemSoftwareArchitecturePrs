#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Спроба прочитати /etc/shadow через sudo...\n");
    // Якщо користувач має права sudo, команда виконається успішно
    int status = system("sudo cat /etc/shadow");
    
    if (status == -1) {
        perror("Помилка виконання system");
    }
    return 0;
}