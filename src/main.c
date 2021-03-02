#include <stdio.h>
#include <stdlib.h>

/// Array of integers - line of the matrix
typedef struct IntArray {
    int *elem;
    int n;
} IntArray;

/// integer matrix - consists of integer lines (arrays)
typedef struct IntMatrix {
    IntArray *line;
    int m;
} IntMatrix;

int readInt(int *);
int readIntMatrix(IntMatrix *);
void printIntMatrix(const IntMatrix*);
void freeIntMatrix(IntMatrix *);

int transformIntMatrix(const IntMatrix*, IntMatrix*);
int digSum(int);

int main() {
    IntMatrix matrix = {NULL, 0};
    if (!readIntMatrix(&matrix)) {
        puts("Error while reading matrix");
        return -1;
    }
    IntMatrix result = {NULL, 0};
    if (!transformIntMatrix(&matrix, &result)) {
        puts("Failed to reallocate memory for new matrix");
        return -1;
    }
    
    puts("----------------");
    puts("Given matrix:");
    printIntMatrix(&matrix);
    puts("New matrix(only digSum(i) == digSum(last)):");
    printIntMatrix(&result);

    freeIntMatrix(&matrix);
    freeIntMatrix(&result);

    return 0;
}

/// read integer and return 1 on success
int readInt(int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            puts("ERROR");
            scanf("%*[^\n]"); // remove all except(until) \n
        }
    } while (n == 0);
    return n < 0 ? 0 : 1;
}

/// read int matrix and return 1 on success
int readIntMatrix(IntMatrix *mat) {
    int m = 0;
    while(readInt(&m) && m < 1)
        puts("It's wrong number of lines");
    if (m == 0) // readInt returned 0
        return 0;
    mat->m = m;
    mat->line = malloc(m * sizeof(IntArray));
    for(int i = 0; i < mat->m; ++i) {
        m = 0;
        while(readInt(&m) && m < 1)
            puts("Wrong number of elements in line");
        if (m == 0) { // readInt returned 0
            mat->m = i; // how much lines are already allocated
            freeIntMatrix(mat);
            return 0;
        }
        mat->line[i].n = m;
        mat->line[i].elem = malloc(m * sizeof(int));
        for(int j = 0; j < mat->line[i].n; ++j) {
            if (readInt(&m) == 0) {
                puts("Error while reading line element");
                mat->m = i + 1;
                freeIntMatrix(mat);
                return 0;
            }
            mat->line[i].elem[j] = m;
        }

    }
    return 1;
}

/// print integer matrix
void printIntMatrix(const IntMatrix *mat) {
    for(int i = 0; i < mat->m; ++i) {
        for(int j = 0; j < mat->line[i].n; ++j)
            printf("%d ", mat->line[i].elem[j]);
        printf("\n");
    }
}

/// free integer matrix
void freeIntMatrix(IntMatrix *mat) {
    for(int i = 0; i < mat->m; ++i)
        free(mat->line[i].elem);
    free(mat->line);
    mat->line = NULL;
    mat->m = 0;
}

/// create specific transformed copy of the matrix from source(src) to destination(dst)
/// return 0 if it failed
int transformIntMatrix(const IntMatrix *src, IntMatrix *dst) {
    // dst should be not allocated empty matrix
    dst->m = src->m;
    dst->line = malloc(dst->m * sizeof(IntArray));
    for(int i = 0; i < src->m; ++i) {
        // init variables
        dst->line[i].elem = malloc(src->line[i].n * sizeof(int));
        int last_sum = digSum(src->line[i].elem[src->line[i].n - 1]);
        int dstj = 0;
        // copy wich needed
        for(int j = 0; j < src->line[i].n - 1; ++j)
            if (digSum(src->line[i].elem[j]) == last_sum) {
                dst->line[i].elem[dstj] = src->line[i].elem[j];
                dstj++;
            }
        // add last element
        dst->line[i].elem[dstj] = src->line[i].elem[src->line[i].n - 1];
        dstj++;
        dst->line[i].n = dstj;
        // realloc memory for effective use
        dst->line[i].elem = realloc(dst->line[i].elem, dstj * sizeof(int));
        if (!dst->line[i].elem) {
            dst->m = i;
            freeIntMatrix(dst);
            return 0;
        }
    }
    return 1;
}

/// digits sum of the number 
int digSum(int a) {
    int sum = 0;
    int x = a < 0 ? -a : a;
    do {
        sum += x % 10;
        x /= 10;
    } while (x > 0);
    return sum;
}