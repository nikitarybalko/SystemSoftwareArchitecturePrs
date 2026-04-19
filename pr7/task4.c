#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2...]\n", argv[0]);
        return 1;
    }

    int line_count = 0;
    char line[1024];

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) continue;

        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            line_count++;

            if (line_count % 20 == 0) {
                printf("\n--- Press Enter to continue ---\n");
                getchar();
            }
        }
        fclose(file);
    }
    return 0;
}