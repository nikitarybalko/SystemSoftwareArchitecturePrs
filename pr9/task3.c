#include <stdio.h>
#include <stdlib.h>

int main(void) {
    system("echo 'Дані користувача' > user_file.txt");
    
    system("sudo cp user_file.txt ~/root_copy.txt");
    system("sudo chown root:root ~/root_copy.txt");
    
    printf("Спроба змінити файл root...\n");
    if (system("echo 'Нові дані' >> ~/root_copy.txt") != 0) {
        printf("-> Очікувано: Відмовлено в доступі (Permission denied).\n");
    }

    printf("Спроба видалити файл root...\n");
    if (system("rm -f ~/root_copy.txt") == 0) {
        printf("-> Файл успішно видалено!\n");
    }
    
    system("rm -f user_file.txt");
    return 0;
}