#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("\n[!!!] Фейковий ls!\n\n");

    argv[0] = "/bin/ls";
    execv("/bin/ls", argv);
    
    perror("execv failed");
    return 1;
}