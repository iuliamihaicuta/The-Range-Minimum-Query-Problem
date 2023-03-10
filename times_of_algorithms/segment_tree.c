// https://www.geeksforgeeks.org/segment-tree-range-minimum-query/
// C program for range minimum query using segment tree
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include <time.h>
#define CHECK_TIME(x) {\
    struct timespec start,end;\
    clock_gettime(CLOCK_REALTIME, &start);\
    x;\
    clock_gettime(CLOCK_REALTIME, &end);\
    double f = ((double)end.tv_sec*1e9 + end.tv_nsec) - ((double)start.tv_sec*1e9 + start.tv_nsec); \
    printf("time %f ms\n",f/1000000); \
}

// A utility function to get minimum of two numbers
int minVal(int x, int y) { return (x < y)? x: y; }
  
// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) {  return s + (e -s)/2;  }
  
/*  A recursive function to get the minimum value in a given range
     of array indexes. The following are parameters for this function.
  
    st    --> Pointer to segment tree
    index --> Index of current node in the segment tree. Initially
              0 is passed as root is always at index 0
    ss & se  --> Starting and ending indexes of the segment represented
                  by current node, i.e., st[index]
    qs & qe  --> Starting and ending indexes of query range */
int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
{
    // If segment of this node is a part of given range, then return
    //  the min of the segment
    if (qs <= ss && qe >= se)
        return st[index];
  
    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return INT_MAX;
  
    // If a part of this segment overlaps with the given range
    int mid = getMid(ss, se);
    return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
                  RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}
  
// Return minimum of elements in range from index qs (query start) to
// qe (query end).  It mainly uses RMQUtil()
int RMQ(int *st, int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }
  
    return RMQUtil(st, 0, n-1, qs, qe, 0);
}
  
// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
    // If there is one element in array, store it in current node of
    // segment tree and return
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }
  
    // If there are more than one elements, then recur for left and
    // right subtrees and store the minimum of two values in this node
    int mid = getMid(ss, se);
    st[si] =  minVal(constructSTUtil(arr, ss, mid, st, si*2+1),
                     constructSTUtil(arr, mid+1, se, st, si*2+2));
    return st[si];
}
  
/* Function to construct segment tree from given array. This function
   allocates memory for segment tree and calls constructSTUtil() to
   fill the allocated memory */
int *constructST(int arr[], int n)
{
    // Allocate memory for segment tree
  
    //Height of segment tree
    int x = (int)(ceil(log2(n))); 
  
    // Maximum size of segment tree
    int max_size = 2*(int)pow(2, x) - 1; 
  
    int *st = malloc(max_size * sizeof(int)); 
  
    // Fill the allocated memory st
    constructSTUtil(arr, 0, n-1, st, 0);
  
    // Return the constructed segment tree
    return st;
}
  
// Driver program to test above functions
void segment_tree(char *test_in)
{
    FILE *in_file = fopen(test_in, "r");
    FILE *out_file = fopen("test.out", "w");

    int N, M;

    fscanf(in_file, "%d%d", &N, &M);

    int *array = malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) {
        fscanf(in_file, "%d", &array[i]);
    }
  
    // Build segment tree from given array
    int *st = constructST(array, N);

    for (int i = 0; i < M; ++i) {
        int qs, qe;
        fscanf(in_file, "%d%d", &qs, &qe);

        int min = RMQ(st, N, qs, qe);
        fprintf(out_file, "%d\n", min);
    }
}

int main(void) {
    char filename[15];
    for (int i = 0; i < 64; ++i) {
        sprintf(filename, "in//test%d.in", i + 1);
        printf("%d ", i + 1);
        CHECK_TIME(segment_tree(filename));
    }
}