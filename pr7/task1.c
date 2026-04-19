#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *rwho_out = popen("who", "r");
    FILE *more_in = popen("more", "w");
    char buffer[256];

    if (!rwho_out || !more_in) {
        perror("popen error");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), rwho_out) != NULL) {
        fputs(buffer, more_in);
    }

    pclose(rwho_out);
    pclose(more_in);
    return 0;
}