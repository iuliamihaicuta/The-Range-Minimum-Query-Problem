// https://www.geeksforgeeks.org/sparse-table/ - C++
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <time.h>
#define CHECK_TIME(x) {\
    struct timespec start,end;\
    clock_gettime(CLOCK_REALTIME, &start);\
    x;\
    clock_gettime(CLOCK_REALTIME, &end);\
    double f = ((double)end.tv_sec*1e9 + end.tv_nsec) - ((double)start.tv_sec*1e9 + start.tv_nsec); \
    printf("time %f ms\n",f/1000000); \
}
 
// Fills lookup array lookup[][] in bottom up manner.
void buildSparseTable(int arr[], int n, int **lookup)
{
    // Initialize M for the intervals with length 1
    for (int i = 0; i < n; i++)
        lookup[i][0] = arr[i];
 
    // Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
 
        // Compute minimum value for all intervals with
        // size 2^j
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
 
            // For arr[2][10], we compare arr[lookup[0][7]]
            // and arr[lookup[3][10]]
            if (lookup[i][j - 1] <
                        lookup[i + (1 << (j - 1))][j - 1])
                lookup[i][j] = lookup[i][j - 1];
            else
                lookup[i][j] =
                         lookup[i + (1 << (j - 1))][j - 1];
        }
    }
}
 
// Returns minimum of arr[L..R]
int query(int L, int R, int **lookup)
{
    // Find highest power of 2 that is smaller
    // than or equal to count of elements in given
    // range. For [2, 10], j = 3
    int j = (int)log2(R - L + 1);
 
    // Compute minimum of last 2^j elements with first
    // 2^j elements in range.
    // For [2, 10], we compare arr[lookup[0][3]] and
    // arr[lookup[3][3]],
    if (lookup[L][j] <= lookup[R - (1 << j) + 1][j])
        return lookup[L][j];
 
    else
        return lookup[R - (1 << j) + 1][j];
}
 
// Driver program
void sparse_table(char *test_in)
{
    FILE *in_file = fopen(test_in, "r");
    FILE *out_file = fopen("test.out", "w");

    int N, M;

    fscanf(in_file, "%d%d", &N, &M);

    int *array = malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) {
        fscanf(in_file, "%d", &array[i]);
    }

    // lookup[i][j] is going to store minimum
    // value in arr[i..j].
    int **lookup = malloc(sizeof(int *) * N);
    for (int i = 0; i < N; ++i)
        lookup[i] = (int *)malloc(sizeof(int) * log2(N));

    buildSparseTable(array, N, lookup);

    for (int i = 0; i < M; ++i) {
        int qs, qe;
        fscanf(in_file, "%d%d", &qs, &qe);
        fprintf(out_file, "%d\n", query(qs, qe, lookup));
    }

    fclose(in_file);
    fclose(out_file);
}

int main(void) {
    char filename[15];
    for (int i = 0; i < 64; ++i) {
        printf("%d: ", i + 1);
        sprintf(filename, "in//test%d.in", i + 1);
        CHECK_TIME(sparse_table(filename));
    }
}
