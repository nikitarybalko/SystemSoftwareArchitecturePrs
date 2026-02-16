#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <limits.h>

int global_init_var = 42;

int global_uninit_var;

const int read_only_var = 100;

int main() {
    time_t max_time;
    
    printf("time_t size: %zu bytes (%zu bits)\n", sizeof(time_t), sizeof(time_t) * 8);

    if (sizeof(time_t) == 4) {
        max_time = (time_t)((1ULL << 31) - 1); 
    } else {
        max_time = (time_t)((1ULL << 63) - 1);
    }

    printf("Max time_t value: %ld\n", (long)max_time);

    struct tm *ts = gmtime(&max_time);
    
    if (ts != NULL) {
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S UTC", ts);
        printf("End of time Unix: %s\n", buf);
    } else {
        printf("Error converting date: the number is too big\n");
    }

    return 0;
}