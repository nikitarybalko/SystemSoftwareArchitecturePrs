#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/resource.h>
#include <errno.h>
#include <time.h>

volatile sig_atomic_t limit_reached = 0;

void signal_handler(int signum) {
    if (signum == SIGXFSZ) {
        limit_reached = 1;
    }
}

int main() {
    struct rlimit rl;
    rl.rlim_cur = 50 * 1024;
    rl.rlim_max = 50 * 1024;

    if (setrlimit(RLIMIT_FSIZE, &rl) != 0) {
        perror("setrlimit failed");
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGXFSZ, &sa, NULL) == -1) {
        perror("sigaction failed");
        return 1;
    }

    FILE *f = fopen("dice_rolls.txt", "w");
    if (!f) {
        perror("fopen failed");
        return 1;
    }

    srand(time(NULL));
    int rolls_count = 0;

    printf("File size limit set to %lu bytes.\n", (unsigned long)rl.rlim_cur);
    printf("Starting dice rolls simulation...\n\n");

    while (!limit_reached) {
        int roll = (rand() % 6) + 1;
        int written = fprintf(f, "Roll %d: %d\n", rolls_count + 1, roll);
        
        if (written < 0) {
            if (errno == EFBIG) {
                printf("System write error caught: File too large (EFBIG).\n");
            } else {
                perror("fprintf error");
            }
            break;
        }
        
        fflush(f);
        rolls_count++;
    }

    if (limit_reached) {
        printf("Received SIGXFSZ signal from the OS!\n");
    }

    fclose(f);

    printf("----------------------------------------\n");
    printf("EXPERIMENT RESULTS:\n");
    printf("Successfully recorded rolls: %d\n", rolls_count);

    return 0;
}