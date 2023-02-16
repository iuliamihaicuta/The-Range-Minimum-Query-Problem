// https://www.geeksforgeeks.org/range-minimum-query-for-static-array/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SQRSIZE  1000

int block[SQRSIZE];          // decomposed array
int blk_sz;                      // block size
  
// Time Complexity : O(sqrt(n))
int query(int arr[], int l, int r)
{
    int min = arr[l];
    while (l<r && l%blk_sz!=0 && l!=0)
    {
        // traversing first block in range
        if (arr[l] < min)
            min = arr[l];

        l++;
    }
    while (l+blk_sz-1 <= r)
    {
        // traversing completely overlapped blocks in range
        if (block[l/blk_sz] < min)
            min = block[l/blk_sz];

        l += blk_sz;
    }
    while (l<=r)
    {
        // traversing last block in range
        if (arr[l] < min)
            min = arr[l];
        l++;
    }
    return min;
}
  
// Fills values in input[]
void preprocess(int arr[], int n)
{
    // initiating block pointer
    int blk_idx = -1;
  
    // calculating size of block
    blk_sz = sqrt(n);
  
    // building the decomposed array
    for (int i=0; i<n; i++)
    {
        if (i%blk_sz == 0)
        {
            // entering next block
            // incrementing block pointer
            blk_idx++;
            block[blk_idx] = arr[i];
        }

        if (arr[i] < block[blk_idx])
            block[blk_idx] = arr[i];
    }
}
  
// Driver code
int main()
{
    // We have used separate array for input because
    // the purpose of this code is to explain SQRT
    // decomposition in competitive programming where
    // we have multiple inputs.
    FILE *in_file = fopen("test.in", "r");
    FILE *out_file = fopen("test.out", "w");

    int N, M;

    fscanf(in_file, "%d%d", &N, &M);

    int *array = malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) {
        fscanf(in_file, "%d", &array[i]);
    }
  
    preprocess(array, N);
  
    for (int i = 0; i < M; ++i) {
        int qs, qe;
        fscanf(in_file, "%d%d", &qs, &qe);
        fprintf(out_file, "%d\n", query(array, qs, qe));
    }

    free(array);
    fclose(in_file);
    fclose(out_file);

    return 0;
}