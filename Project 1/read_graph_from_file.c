#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    
    
    fp = fopen(filename, "r");

    int edges;

    getline(&line, &len, fp);
    getline(&line, &len, fp);    
    
    fscanf(fp, "%*s %*s %d %*s %d", N, &edges );
    printf("%d %d \n", *N, edges);
    getline(&line, &len, fp);
    getline(&line, &len, fp);

   
    int from_arr = 0;
    int to_arr = 0;

    int *row_count = malloc(*N*sizeof(int));
    int *L_count = malloc(*N*sizeof(int));

    memset(row_count, 0, *N*sizeof(int));
    memset(L_count, 0, *N*sizeof(int));
    

    *row_ptr = malloc(((*N)+1)*sizeof(int));
    (*row_ptr)[0] = 0;
    
    

    for (size_t i= 0; i < edges; i++){
        fscanf(fp, "%d %d", &from_arr, &to_arr);

        row_count[to_arr] += 1;
        L_count[from_arr] += 1;
        
    }
    

    for (size_t i = 0; i < *N; i++)
    {
        
        (*row_ptr)[i+1] = (*row_ptr)[i] + row_count[i] ;
        
        
    }
    printf("\n");
    
    /* Prep file to be read again */
    rewind(fp);

    

    

    /* Skip the first 4 lines in file */
    getline(&line, &len, fp); 
    getline(&line, &len, fp);
    getline(&line, &len, fp);
    getline(&line, &len, fp);
    

    *col_idx = malloc(edges*sizeof(int));
    int *count = malloc(*N*sizeof(int));
    *val = malloc(edges*sizeof(double));
    
    /* Insert number in all vectors, avoiding random numbers */
    memset(count, 0, *N*sizeof(int));
    memset(*val, 0, edges*sizeof(double));
    memset(*col_idx, *N, edges*sizeof(int));
    
    from_arr = 0;
    to_arr = 0;
 
    

    for (size_t i = 0; i < edges; i++)
     {
        fscanf(fp, "%d %d", &from_arr, &to_arr);

        
        (*col_idx)[(*row_ptr)[to_arr] + count[to_arr]] = from_arr;
        (*val)[(*row_ptr)[to_arr] + count[to_arr]] = 1. / L_count[from_arr];
        count[to_arr] += 1;
        
        
        //for (size_t j = 0; j < (*row_ptr)[to_arr+1] - (*row_ptr)[to_arr]; j++){
        //    if (from_arr < (*col_idx)[(*row_ptr)[to_arr] + j]){
        //        /* Move number to the right*/
        //        for (size_t k = count[to_arr]; k > j; k--)
        //            { 
        //               (*col_idx)[(*row_ptr)[to_arr] + k] = (*col_idx)[(*row_ptr)[to_arr] + k-1];
        //               (*val)[(*row_ptr)[to_arr] + k] = (*val)[(*row_ptr)[to_arr] + k-1];
        //            }
        //        /* Assign value to correct place */
        //        (*col_idx)[(*row_ptr)[to_arr] + j] = from_arr;
        //        (*val)[(*row_ptr)[to_arr] + j] = 1./L_count[from_arr];
        //        count[to_arr] += 1;
        //        break;
        //    }
        //}
    }

    
   
    
    free(count); free(L_count); free(row_count); free(line);

    fclose(fp);
    

}
