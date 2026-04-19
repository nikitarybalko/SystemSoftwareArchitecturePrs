#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[256];
    uid_t my_uid = getuid();

    printf("Мій UID: %d\n", my_uid);
    printf("Інші звичайні користувачі (UID >= 1000):\n");

    while (fgets(line, sizeof(line), fp)) {
        char *user = strtok(line, ":");
        strtok(NULL, ":");
        char *uid_str = strtok(NULL, ":");
        
        if (uid_str) {
            int uid = atoi(uid_str);
            if (uid >= 1000 && uid != 65534 && uid != my_uid) {
                printf("- Користувач: %s (UID: %d)\n", user, uid);
            }
        }
    }
    pclose(fp);
    return 0;
}