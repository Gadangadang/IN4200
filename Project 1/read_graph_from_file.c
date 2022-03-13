#include <stdio.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(filename, "r");

    int edges;

    for (int i = 0; i < 1; ++i)
        getline(&line, &len, fp); /* Skip the first 2 lines in file */

    
    getline(&line, &len, fp);
    fscanf(fp, "%*s %*s %d %*s %d", N, &edges );
    printf("%d %d \n", *N, edges);
    getline(&line, &len, fp);

   
    /* Create L(j) arr */

    

    int from_arr = 0;
    int to_arr = 0;

    int *row_count = (int*)malloc(*N*sizeof(int));
    int *L_count = (int*)malloc(*N*sizeof(int));
    *row_ptr = (int*)malloc(*N*sizeof(int)+1);
    (*row_ptr)[0] = 0;
    
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        fscanf(fp, "%d %d", &from_arr, &to_arr);
        row_count[to_arr] += 1;
        L_count[from_arr] += 1;
        printf("From node %d to node %d\n", from_arr, to_arr);
        i+=1;
    }

    for (size_t i = 0; i < *N; i++)
    {
        
        (*row_ptr)[i+1] = (*row_ptr)[i] + row_count[i] ;
        printf("%d", row_count[i]);
        
    }
    printf("\n");
    for (size_t i = 0; i < *N+1; i++)
    {
        printf("%d", (*row_ptr)[i]);
    }
    
    if (line)
        free(line);

    fclose(fp);

    printf("\n");
    printf("\n");

    fp = fopen(filename, "r");

    for (int i = 0; i < 1; ++i)
        getline(&line, &len, fp); /* Skip the first 2 lines in file */

    
    getline(&line, &len, fp);
    getline(&line, &len, fp);


    *col_idx = (int*)malloc(edges*sizeof(int));
    int *count = (int*)malloc(*N*sizeof(int));
    *val = (double*)malloc(edges*sizeof(double));
    for (int i = 0; i < edges; i++) (*col_idx)[i] = *N;
    
    from_arr = 0;
    to_arr = 0;
 
 
    while ((read = getline(&line, &len, fp)) != -1) {
        fscanf(fp, "%d %d", &from_arr, &to_arr);
        
        
        for (size_t j = 0; j < (*row_ptr)[to_arr+1] - (*row_ptr)[to_arr]; j++){
            if (from_arr < (*col_idx)[(*row_ptr)[to_arr] + j]){
                /* Move number to the right*/
                for (size_t k = count[to_arr]; k > j; k--)
                    { 
                       (*col_idx)[(*row_ptr)[to_arr] + k] = (*col_idx)[(*row_ptr)[to_arr] + k-1];
                       (*val)[(*row_ptr)[to_arr] + k] = (*val)[(*row_ptr)[to_arr] + k-1];
                    }

                (*col_idx)[(*row_ptr)[to_arr] + j] = from_arr;
                (*val)[(*row_ptr)[to_arr] + j] = 1./L_count[from_arr];
                count[to_arr] += 1;
                break;
            }
            
            
        }
        
        
        
        
    }

    
    for (size_t i = 0; i < edges; i++)
    {
        printf("%d, %f \n", (*col_idx)[i], (*val)[i]);
    }
    
    

    fclose(fp);

}
