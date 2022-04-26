#ifndef PAGERANK_ITERATIONS_H /* Include guard */
#define PAGERANK_ITERATIONS_H

#include <math.h>

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);

#endif // FUNCTIONS_PARALLEL