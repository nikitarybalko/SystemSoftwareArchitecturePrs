#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>
#include <unistd.h>

// Функція-колбек, яка викликається для кожного знайденого файлу
int check_anomaly(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    // Перевіряємо лише звичайні файли (ігноруємо каталоги, посилання тощо)
    if (tflag == FTW_F && S_ISREG(sb->st_mode)) {
        
        // Перевіряємо, чи є файл виконуваним хоча б для когось
        int is_executable = sb->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH);
        
        if (is_executable) {
            int is_suid = sb->st_mode & S_ISUID;
            int is_sgid = sb->st_mode & S_ISGID;
            int is_world_writable = sb->st_mode & S_IWOTH;

            // Якщо є хоча б одна з аномалій, виводимо інформацію
            if (is_suid || is_sgid || is_world_writable) {
                printf("[!] Аномалія: %s\n", fpath);
                if (is_suid) printf("    -> Встановлено SUID біт (Загроза підвищення привілеїв)\n");
                if (is_sgid) printf("    -> Встановлено SGID біт\n");
                if (is_world_writable) printf("    -> Файл відкритий для запису всім (World-writable!)\n");
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // За замовчуванням скануємо поточний каталог, якщо не передано інший
    const char *dir = (argc > 1) ? argv[1] : ".";
    
    int flags = FTW_PHYS; 
    
    printf("Розпочато сканування каталогу: %s\n", dir);
    printf("Шукаємо SUID/SGID та World-writable виконувані файли...\n\n");

    if (nftw(dir, check_anomaly, 20, flags) == -1) {
        perror("Помилка під час обходу каталогів (nftw)");
        return 1;
    }

    printf("\nСканування завершено.\n");
    return 0;
}