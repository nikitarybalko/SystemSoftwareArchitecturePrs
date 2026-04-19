#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat st;
    char answer[10];

    if (!dir) return 1;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            printf("Delte file %s? (y/n): ", entry->d_name);
            if (fgets(answer, sizeof(answer), stdin) && answer[0] == 'y') {
                if (unlink(entry->d_name) == 0) {
                    printf("File deleted\n");
                } else {
                    perror("unlink error");
                }
            }
        }
    }
    closedir(dir);
    return 0;
}