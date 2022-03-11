#include <stdio.h>

void read_graph_from_file(char *filename){//, int *N, int**row_ptr, int **col_idx, double **val){

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char buff[255];
    fp = fopen(filename, "r");

    int nodes, edges;

    char str1[10], str2[10];
    

    for (int i = 0; i < 1; ++i)
        getline(&line, &len, fp); /* Skip the first 2 lines in file */

    
    getline(&line, &len, fp);
    fscanf(fp, "%*s %*s %d %*s %d", &nodes, &edges );
    printf("%d %d \n", nodes, edges);
    
    while ((read = getline(&line, &len, fp)) != -1) {
        fscanf(fp, "%s %s", str1, str2);
        printf("From node %s to node %s\n", str1, str2);


        
    }

    if (line)
        free(line);

    fclose(fp);
}