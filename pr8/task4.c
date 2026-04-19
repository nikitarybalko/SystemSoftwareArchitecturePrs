#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pid;
    pid = fork();
    
    printf("%d\n", pid);
    
    // Чекаємо завершення дитини, щоб консоль не зламалась після виходу
    if (pid > 0) {
        wait(NULL); 
    }
    return 0;
}