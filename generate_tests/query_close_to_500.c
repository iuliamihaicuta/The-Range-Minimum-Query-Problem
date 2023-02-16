#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define SWAP(x,y) { x = x + y; y = x - y; x = x - y; }

int N[5] = {1000, 10000, 100000, 1000000};

int find_minimum_in_range(int *array, int x, int y) {
    int min = array[x];

    for (int i = x; i < y; ++i)
        if (array[i] < min)
            min = array[i];

    return min;
}



int main(void) {
    char filename[12];
    char resultsFilename[12];
    int aux = 33;

    // lenght of each query close to 500
    for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
            sprintf(filename, "..//in//test%d.in", aux);
            FILE *new_test = fopen(filename, "w");

            sprintf(resultsFilename, "..//out//test%d.out", aux);
            FILE *results = fopen(resultsFilename, "w");

            fprintf(new_test, "%d %d\n", N[j], N[k]);

            int *numbers = (int *)malloc(N[j] * sizeof(int));

            for (int m = 0; m < N[j]; ++m) {
                numbers[m] = rand();
                fprintf(new_test, "%d ", numbers[m]);
            }
            fprintf(new_test, "\n");

            for (int m = 0; m < N[k]; ++m) {
                int x = rand() % (N[j] - 600) + 1;
                int y = rand() % 100 + 450 + x;

                fprintf(new_test, "%d %d\n", x, y);
                fprintf(results, "%d\n", find_minimum_in_range(numbers, x, y));
            }
            free(numbers);
            fclose(new_test);
            fclose(results);

            ++aux;
        }
    }

    return 0;
}