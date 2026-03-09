#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PAGE_SIZE 4096      // 4 КБ
#define NUM_PAGES 25600

int main() {
    size_t size = NUM_PAGES * PAGE_SIZE;    // 25600 сторінок * 4 КБ = 100 МБ
    
    // Виділяємо великий блок пам'яті (100 МБ)
    char *buffer = malloc(size);
    if (!buffer) {
        perror("Memory allocation error");
        return 1;
    }

    // Заповнюємо пам'ять даними
    memset(buffer, 1, size);
    printf("[Parent] Allocated 100 MB. Press Enter to execute fork()...\n");
    getchar();

    // Створюємо дочірній процес
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    } 
    else if (pid == 0) {
        printf("[Child] Created. For now memory is common with the parent (COW).\n");
        printf("[Child] Press Enter to change 1 byte per page...\n");
        getchar();

        // Суть COW: змінюємо лише ОДИН байт на кожній сторінці.
        // Загалом ми змінимо лише 25 КБ даних, але ОС буде змушена 
        // скопіювати кожну сторінку по 4 КБ, тому RSS різко зросте на 100 МБ.
        for (size_t i = 0; i < size; i += PAGE_SIZE) {
            buffer[i] = 2; 
        }

        printf("[Child] Memory changed! COW happened, RSS of the child process has increased drastically.\n");
        printf("[Child] Press Enter to end...\n");
        getchar();
        
        free(buffer);
        return 0;
    } else {
        wait(NULL);
        free(buffer);
        printf("[Parent] Child process is complete.\n");
    }

    return 0;
}