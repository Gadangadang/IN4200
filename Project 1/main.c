#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "read_graph_from_file.c"
#include "PageRank_iterations.c"


int main(int argc, char **argv){
    char *filename;
    filename = argv[1];

    double d = atof(argv[2]);
    double epsilon = atof(argv[3]);
    int n = atoi(argv[4]);

    int *row_ptr, *col_idx;
    double *val;
    int N;

    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);

    
    
    double *scores = (double*)malloc(N*sizeof(double));
    for (int i = 0; i < N ; ++i) {
        scores[i] = 1./(N);
        
    }
    

    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);

}