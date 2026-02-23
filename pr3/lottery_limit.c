#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t cpu_limit_reached = 0;

void handle_sigxcpu(int signum) {
    if (signum == SIGXCPU) {
        cpu_limit_reached = 1;
    }
}

void generate_lottery(int max_val, int count, int* result) {
    int selected = 0;
    while (selected < count) {
        int num = (rand() % max_val) + 1;
        int unique = 1;
        for (int i = 0; i < selected; i++) {
            if (result[i] == num) {
                unique = 0;
                break;
            }
        }
        if (unique) {
            result[selected++] = num;
        }
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigxcpu;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGXCPU, &sa, NULL) == -1) {
        perror("sigaction failed");
        return 1;
    }

    struct rlimit rl;
    rl.rlim_cur = 1; 
    rl.rlim_max = 2; 

    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("setrlimit failed");
        return 1;
    }

    srand(time(NULL));

    unsigned long long iterations = 0;
    int lotto1[7];
    int lotto2[6];

    printf("CPU time limit set to %ld second(s).\n", (long)rl.rlim_cur);
    printf("Generating lottery combinations (7/49 and 6/36)...\n");

    while (!cpu_limit_reached) {
        generate_lottery(49, 7, lotto1);
        generate_lottery(36, 6, lotto2);

        iterations++;
        
        if (iterations % 500000 == 0) {
            printf("Iteration %llu: [ ", iterations);
            for(int i = 0; i < 7; i++) printf("%d ", lotto1[i]);
            printf("] and [ ");
            for(int i = 0; i < 6; i++) printf("%d ", lotto2[i]);
            printf("]\n");
        }
    }

    printf("\n[!] Caught SIGXCPU signal! CPU time limit exceeded.\n");
    printf("----------------------------------------\n");
    printf("EXPERIMENT RESULTS:\n");
    printf("Total combinations generated: %llu\n", iterations);

    return 0;
}