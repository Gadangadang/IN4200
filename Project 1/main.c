#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "read_graph_from_file.c"


int main(int argc, char **argv){
    char *filename;
    filename = argv[1];

    double d = atof(argv[2]);
    double epsilon = atof(argv[3]);
    int n = atoi(argv[4]);
    read_graph_from_file(filename);
}