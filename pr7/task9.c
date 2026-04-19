#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(void) {
    struct timeval start, end;
    
    gettimeofday(&start, NULL);

    printf("Doing work...\n");
    usleep(150000);

    gettimeofday(&end, NULL);

    long mtime = ((end.tv_sec - start.tv_sec) * 1000) + 
                 ((end.tv_usec - start.tv_usec) / 1000);

    printf("Execution time: %ld ms\n", mtime);
    return 0;
}
