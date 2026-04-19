#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_perms(mode_t mode) {
    printf("%c", S_ISDIR(mode) ? 'd' : (S_ISLNK(mode) ? 'l' : '-'));
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c ", (mode & S_IXOTH) ? 'x' : '-');
}

int main(void) {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat file_stat;

    if (!dir) return 1;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == -1) continue;

        print_perms(file_stat.st_mode);
        printf("%lu ", (unsigned long)file_stat.st_nlink);
        
        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group  *gr = getgrgid(file_stat.st_gid);
        printf("%s %s ", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
        
        printf("%8lld ", (long long)file_stat.st_size);
        
        char time_buf[64];
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf("%s %s\n", time_buf, entry->d_name);
    }
    closedir(dir);
    return 0;
}