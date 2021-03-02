#include <stdio.h>
#include <stdlib.h>

int getInt(int *);
int readIntArr(int *, int);
void printIntArr(int *, int);

void quicksort(int *, int, int);
int partition(int *, int, int);
void swap(int *, int *);

int count_zeros(int);
int count_len(int);

int main() {
    // read n
    int n;
    if (getInt(&n) == 0) {
        puts("Error while reading n");
        return -1;
    }
    // alloc&read data[n]
    int *data = malloc(n * sizeof(int));
    if (readIntArr(data, n) == 0) {
        puts("Error while reading array");
    }
    // sort data[n]
    quicksort(data, 0, n - 1);
    // print data[n]
    printIntArr(data, n);
    // print zero_num for each data[n]
    for(int i = 0; i < n - 1; ++i) {
        printf("%d ", count_zeros(data[i]));
    }
    printf("%d\n", count_zeros(data[n - 1]));
    // print int_len for each data[n]
    for(int i = 0; i < n - 1; ++i) {
        printf("%d ", count_len(data[i]));
    }
    printf("%d\n", count_len(data[n - 1]));

    free(data);

    return 0;
}

int getInt(int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            puts("ERROR");
            // scanf("%*c");     // remove all chars
            scanf("%*[^\n]"); // remove all except(until) \n
            // scanf("%*s");   %d  // remove all until space symbol
        }
    } while (n == 0);
    return n < 0 ? 0 : 1;
}

int readIntArr(int *data, int n) {
    for(int i = 0; i < n; ++i) {
        if (getInt(&data[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

void printIntArr(int *data, int n) {
    for(int i = 0; i < n - 1; ++i) {
        printf("%d ", data[i]);
    }
    printf("%d\n", data[n - 1]);
}

void quicksort(int *data, int low, int high) {
    if (low < high) {
        int pivot = partition(data, low, high);
        quicksort(data, low, pivot - 1);
        quicksort(data, pivot + 1, high);
    } 
}

int partition(int *data, int low, int high) {
    int pivot = data[(low + high) / 2];
    for(;;) {
        while (data[low] < pivot) { low++; }
        while (data[high] > pivot) { high--; }
        if (low >= high) {
            return high;
        }
        swap(&data[low], &data[high]);
    }
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int count_zeros(int a) {
    int c, cnt = 0;
    int x = a < 0 ? -a : a;
    do {
        c = x % 10;
        x /= 10;
        if (c == 0) {
            cnt++;
        }
    } while (x >= 10);
    return cnt;
}

int count_len(int a) {
    int cnt = 0;
    int x = a < 0 ? -a : a;
    do {
        x /= 10;
        cnt++;
    } while (x > 0);
    return cnt;
}