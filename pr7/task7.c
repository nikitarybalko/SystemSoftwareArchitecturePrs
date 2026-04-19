#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(void) {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat st;
    char answer[10];

    if (!dir) return 1;

    while ((entry = readdir(dir)) != NULL) {
        size_t len = strlen(entry->d_name);
        if (len > 2 && strcmp(entry->d_name + len - 2, ".c") == 0) {
            if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
                printf("Give others permission to read %s? (y/n): ", entry->d_name);
                if (fgets(answer, sizeof(answer), stdin) && answer[0] == 'y') {
                    if (chmod(entry->d_name, st.st_mode | S_IROTH) == 0) {
                        printf("Permissions updated\n");
                    } else {
                        perror("chmod error");
                    }
                }
            }
        }
    }
    closedir(dir);
    return 0;
}