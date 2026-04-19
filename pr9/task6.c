#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    printf("Перегляд домашнього каталогу, /usr/bin та /etc:\n");
    system("ls -ld ~ /usr/bin /etc");

    printf("\n--- Спроба взаємодії з файлами ---\n");
    
    // 1. Спроба читання /etc/shadow (належить root:shadow, права -rw-r-----)
    if (access("/etc/shadow", R_OK) != 0) {
        printf("Читання /etc/shadow: Відмовлено (немає прав).\n");
    }

    // 2. Спроба запису в /etc/passwd (належить root:root, права -rw-r--r--)
    if (access("/etc/passwd", W_OK) != 0) {
        printf("Запис в /etc/passwd: Відмовлено (лише для root).\n");
    }

    // 3. Спроба виконання утиліти з /usr/bin (належить root, права rwxr-xr-x)
    if (access("/usr/bin/whoami", X_OK) == 0) {
        printf("Виконання /usr/bin/whoami: Дозволено (встановлено біт виконання для всіх).\n");
    }

    return 0;
}