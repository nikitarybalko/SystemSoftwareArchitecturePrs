#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MIN_SIZE 1
#define MAX_SIZE 1000

void print_memory_status(const char *action,
                          size_t size,
                          size_t capacity,
                          void *ptr)
{
    printf("[MEMORY] %-8s | size=%zu | capacity=%zu | bytes=%zu | ptr=%p\n",
           action,
           size,
           capacity,
           capacity * sizeof(int),
           ptr);
}

int *ensure_capacity(int *arr,
                     size_t *capacity,
                     size_t min_capacity)
{
    if (*capacity >= min_capacity) {
        return arr;
    }

    size_t old_capacity = *capacity;
    size_t new_capacity = old_capacity;

    if (new_capacity < 2) {
        new_capacity = 2;
    }

    while (new_capacity < min_capacity) {
        new_capacity += new_capacity >> 1; // ~1.5x
    }

    int *tmp = realloc(arr, new_capacity * sizeof(int));
    if (tmp == NULL) {
        printf("[ERROR ] realloc error in ensure_capacity()!\n");
        return NULL;
    }

    *capacity = new_capacity;
    print_memory_status("realloc", min_capacity, *capacity, tmp);

    return tmp;
}

void print_array(int *arr, size_t size) {
    printf("Current array:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int n;
    printf("Enter a number (array size): ");
    scanf("%d", &n);

    if (n < MIN_SIZE || n > MAX_SIZE) {
        printf("[ERROR ]: size must be in range from %d to %d (inclusive)\n",
               MIN_SIZE, MAX_SIZE);
        return 1;
    }

    size_t size = n;
    size_t capacity = n;

    int *arr = malloc(capacity * sizeof(int));
    if (arr == NULL) {
        printf("[ERROR ] malloc error in main()!\n");
        return 1;
    }

    print_memory_status("malloc", size, capacity, arr);

    /* Filling array with n */
    for (size_t i = 0; i < size; i++) {
        arr[i] = n;
    }

    printf("[INFO  ] array filled with number %d\n", n);

    print_array(arr, size);

    int running = 1;
    while(running) {
        char answer[10];
        printf("Choose an option:\n");
        printf("N - choose new array size   E - exit\n");
        scanf("%10s", answer);

        if(tolower(answer[0]) == 'n') {
            int new_size;
            printf("Enter new array size: ");
            scanf("%d", &new_size);
        
            if (new_size < MIN_SIZE || new_size > MAX_SIZE) {
                printf("[ERROR ]: size must be in range from %d to %d (inclusive)\n",
                    MIN_SIZE, MAX_SIZE);
                free(arr);
                print_memory_status("free", 0, 0, NULL);
                return 1;
            }
        
            if ((size_t)new_size > capacity) {
                arr = ensure_capacity(arr, &capacity, new_size);
                if (arr == NULL) {
                    return 1;
                }
            }
        
            /* If size changed, initialize with new values */
            if ((size_t)new_size > size) {
                for (size_t i = size; i < (size_t)new_size; i++) {
                    arr[i] = n;
                }
            }
        
            size = new_size;
            print_memory_status("resize", size, capacity, arr);
        
            /* output */
            print_array(arr, size);

        } else if(tolower(answer[0]) == 'e') {
            printf("Bye!\n");
            running = 0;
            break;
        } else {
            printf("'%c' is not an option!\n", answer[0]);
        }
    }

    /* Free up the memory */
    free(arr);
    print_memory_status("free", 0, 0, NULL);

    return 0;
}
