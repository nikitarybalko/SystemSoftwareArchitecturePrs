#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_access(const char *file) {
    printf("Читання (R_OK): %s\n", access(file, R_OK) == 0 ? "ТАК" : "НІ");
    printf("Запис (W_OK): %s\n", access(file, W_OK) == 0 ? "ТАК" : "НІ");
}

int main(void) {
    const char *file = "temp_95.txt";
    system("touch temp_95.txt");
    
    printf("\n[1] Власник: звичайний користувач\n");
    check_access(file);

    printf("\n[2] Власник: root, права: 600 (тільки root)\n");
    system("sudo chown root:root temp_95.txt");
    system("sudo chmod 600 temp_95.txt");
    check_access(file);

    printf("\n[3] Власник: root, права: 666 (читання/запис для всіх)\n");
    system("sudo chmod 666 temp_95.txt");
    check_access(file);

    system("sudo rm -f temp_95.txt");
    return 0;
}