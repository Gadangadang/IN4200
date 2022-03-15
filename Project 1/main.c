#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "read_graph_from_file.c"
#include "PageRank_iterations.c"
#include "top_n_webpages.c"
#include <time.h>

int main(int argc, char **argv){
    /*
    -g as flag and gdb "name of compiled file" to debug line by line
    */

    char *filename;
    filename = argv[1];

    double d = atof(argv[2]);
    double epsilon = atof(argv[3]);
    int n = atoi(argv[4]);

    int *row_ptr, *col_idx;
    double *val;
    int N;

    /* Start timing code */
    clock_t begin1 = clock();

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

    /* Check if n is bigger than N*/
    if (n > N) memcpy(&n, &N, sizeof(int));
    
    
    double *scores = malloc(N*sizeof(double));
   
    for (size_t i = 0; i < N; i++)
    {
       scores[i] = 1./N;
    }

    clock_t begin = clock();
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time page rank is %E sec\n", time_spent);

    top_n_webpages(N, scores, n);

    clock_t end1 = clock();
    double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    printf("Time total is %E min\n", time_spent1/60);

    free(row_ptr); 
    free(col_idx); 
    free(val); 
    free(scores);

    
    return 0;
}



