#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void test_sort(int *arr, int n) {
    for(int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i+1]) {
            printf("[ПОМИЛКА] Масив не відсортовано!\n");
            return;
        }
    }
    printf("[ОК] Відсортовано правильно.\n");
}

int main(void) {
    int n = 5000000;
    int *arr = malloc(n * sizeof(int));
    clock_t start, end;

    printf("Розмір масиву: %d елементів\n\n", n);

    // 1. Випадкові дані (звичайний випадок)
    for(int i=0; i<n; i++) arr[i] = rand();
    start = clock(); qsort(arr, n, sizeof(int), cmp); end = clock();
    printf("Випадковий масив:        %.2f мс ", (double)(end-start)/CLOCKS_PER_SEC * 1000);
    test_sort(arr, n);

    // 2. Вже відсортований масив (найгірший випадок для класичного qsort)
    start = clock(); qsort(arr, n, sizeof(int), cmp); end = clock();
    printf("Вже відсортований:       %.2f мс ", (double)(end-start)/CLOCKS_PER_SEC * 1000);
    test_sort(arr, n);

    // 3. Зворотно відсортований масив (часто найгірший випадок)
    for(int i=0; i<n; i++) arr[i] = n - i;
    start = clock(); qsort(arr, n, sizeof(int), cmp); end = clock();
    printf("Зворотний порядок:       %.2f мс ", (double)(end-start)/CLOCKS_PER_SEC * 1000);
    test_sort(arr, n);
    
    // 4. Масив з однакових елементів (деградує до O(N^2) у старих реалізаціях)
    for(int i=0; i<n; i++) arr[i] = 42;
    start = clock(); qsort(arr, n, sizeof(int), cmp); end = clock();
    printf("Всі однакові елементи:   %.2f мс ", (double)(end-start)/CLOCKS_PER_SEC * 1000);
    test_sort(arr, n);

    free(arr);
    return 0;
}