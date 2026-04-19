#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    int fd = open("test_data.bin", O_CREAT | O_RDWR | O_TRUNC, 0666);
    write(fd, data, sizeof(data)); // Записуємо байти
    
    lseek(fd, 3, SEEK_SET); // Переміщуємо покажчик на зміщення 3
    
    unsigned char buffer[4];
    read(fd, buffer, 4);    // Читаємо 4 байти
    
    printf("Прочитаний буфер: %d, %d, %d, %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);
    
    close(fd);
    unlink("test_data.bin"); // Видаляємо тимчасовий файл
    return 0;
}