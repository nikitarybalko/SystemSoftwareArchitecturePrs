#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int fd = open("shared.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    char *initial = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; // 32 байти
    write(fd, initial, 32);
    
    // Відображаємо файл у пам'ять (mmap)
    char *map = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (fork() == 0) {
        // ДОЧІРНІЙ ПРОЦЕС: перезаписує файл через mmap (пише 'M')
        for(int i = 0; i < 32; i++) {
            map[i] = 'M';
            usleep(50); // Штучна затримка для створення race condition
        }
        munmap(map, 32);
        exit(0);
    } else {
        // БАТЬКІВСЬКИЙ ПРОЦЕС: перезаписує файл через write
        for(int i = 0; i < 32; i++) {
            pwrite(fd, "W", 1, i);
            usleep(50);
        }
        wait(NULL); // Чекаємо дитину
    }
    
    lseek(fd, 0, SEEK_SET);
    char res[33] = {0};
    read(fd, res, 32);
    printf("Змішаний результат файлу:\n%s\n", res);
    
    close(fd);
    return 0;
}