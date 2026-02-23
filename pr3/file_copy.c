#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

volatile sig_atomic_t limit_reached = 0;

void signal_handler(int signum) {
    if (signum == SIGXFSZ) {
        limit_reached = 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n");
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGXFSZ, &sa, NULL);

    // Using POSIX open() instead of fopen()
    int src = open(argv[1], O_RDONLY);
    if (src < 0) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    int dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst < 0) {
        printf("Cannot open file %s for writing\n", argv[2]);
        close(src);
        return 1;
    }

    char buffer[4096];
    ssize_t bytes_read;
    size_t total_copied = 0;

    printf("Starting to copy...\n");

    // Using POSIX read() and write()
    while ((bytes_read = read(src, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(dst, buffer, bytes_read);
        
        if (bytes_written < 0) {
            if (errno == EFBIG || limit_reached) {
                printf("\n[!] File size limit exceeded while writing.\n");
                printf("Copied %zu bytes before the OS stopped the process.\n", total_copied);
            } else {
                printf("\nAn error occurred during writing. Errno: %d\n", errno);
            }
            break;
        }
        total_copied += bytes_written;
    }

    // Checking for success strictly based on read() reaching the end (0)
    if (bytes_read == 0 && !limit_reached) {
        printf("\nFile copied successfully. Total size: %zu bytes.\n", total_copied);
    }

    close(src);
    close(dst);

    return 0;
}