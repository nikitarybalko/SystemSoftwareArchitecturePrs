#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));

    float rand_0_1 = (float)rand() / RAND_MAX;
    printf("Random from 0.0 to 1.0: %f\n", rand_0_1);

    float n = 50.5;
    if (argc > 1) {
        n = atof(argv[1]);
    }
    
    float rand_0_n = ((float)rand() / RAND_MAX) * n;
    printf("Random from 0.0 to %.2f: %f\n", n, rand_0_n);

    return 0;
}
