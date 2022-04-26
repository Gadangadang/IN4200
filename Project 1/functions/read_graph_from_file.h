#ifndef READ_GRAPH_FROM_FILE_H /* Include guard */
#define READ_GRAPH_FROM_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);

#endif // FUNCTIONS_PARALLEL