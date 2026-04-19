#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd[2];
    pipe(fd);
    
    fcntl(fd[1], F_SETFL, O_NONBLOCK);
    
    char buffer[100000] = {0};
    ssize_t nbytes = sizeof(buffer);
    ssize_t count = write(fd[1], buffer, nbytes);
    
    printf("Запитано для запису: %zd байт\n", nbytes);
    printf("Фактично записано:   %zd байт\n", count);
    
    return 0;
}