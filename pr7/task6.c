#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    struct dirent **namelist;
    int n = scandir(".", &namelist, NULL, alphasort);

    if (n < 0) {
        perror("scandir");
        return 1;
    }

    struct stat file_stat;
    for (int i = 0; i < n; i++) {
        if (strcmp(namelist[i]->d_name, ".") != 0 && strcmp(namelist[i]->d_name, "..") != 0) {
            if (stat(namelist[i]->d_name, &file_stat) == 0 && S_ISDIR(file_stat.st_mode)) {
                printf("%s/\n", namelist[i]->d_name);
            }
        }
        free(namelist[i]);
    }
    free(namelist);
    return 0;
}