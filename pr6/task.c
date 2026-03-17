#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Service started. Starting memory leak simulation...\n");
    
    // Імітуємо роботу сервісу (50 ітерацій)
    for(int i = 0; i < 50; i++) {
        // Виділяємо 1 МБ (1024 * 1024 байт) кожну ітерацію
        void *leaked_memory = malloc(1024 * 1024);
        
        if(leaked_memory == NULL) {
            perror("Memory allocation error");
            return 1;
        }
        
        // Навмисно не звільняємо пам'ять, створюючи витік (memory leak)
        
        usleep(100000);
    }

    printf("Work completed. Memory was not freed\n");
    return 0;
}