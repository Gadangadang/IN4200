#include <math.h>

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){
    printf("\n");

    int k = 0;
    int edges = row_ptr[N];
    
    double *x_k_1 = malloc(N*sizeof(double));
    memcpy(x_k_1, scores, N*sizeof(double));
    
    double *x_k = malloc(N*sizeof(double));
    double *Ax_k_1 = malloc(N * sizeof(double));
    double max_err, err, W_k_1, d_term;

    int *non_zero_columns = malloc(N*sizeof(int));
    memset(non_zero_columns, 0, N*sizeof(int));
    int nr_dong = N;

    int *dong_index = malloc(nr_dong*sizeof(int));
    memset(dong_index, 0, nr_dong*sizeof(int));
    int count = 0;
        
    #pragma omp parallel for
    for (size_t i = 0; i < edges; i++)
    {
        non_zero_columns[col_idx[i]] = 1 ;
    }

    #pragma omp parallel for reduction(-:nr_dong)
    for (size_t i = 0; i < N; i++)
    {
        nr_dong -= non_zero_columns[i];
    }

    #pragma omp parallel 
    {
    #pragma omp for
        for (size_t i = 0; i < N; i++)
        {   
            if (non_zero_columns[i] == 0){
                #pragma omp critical
                {
                dong_index[count] = i;
                count +=1;
                }
            }
        }
    }

    printf("\n");
    printf("NR of dangling webpages: %d\n", nr_dong);
    
    printf("\n");

    size_t i, j;
    
    
        while (1){
            
            max_err=0;
            err = 0;
            W_k_1 = 0;

            memset(Ax_k_1, 0, N*sizeof(double));
            memset(x_k, 0, N*sizeof(double));

            /* Calculate W_k_1 */

            W_k_1 = 0;
            
            #pragma omp parallel for schedule(dynamic) reduction(+:W_k_1)
            for (i = 0; i < nr_dong; i++)
            {   
                W_k_1 += x_k_1[dong_index[i]];
            }
            
            d_term = (1-d+d*W_k_1)/(N);
            

            /* Sparse matrix multiplication and filling of x_k */
            #pragma omp parallel private(j) 
            {
            #pragma omp for schedule(dynamic) 
            for (i = 0; i < N; i++)
            {
                for (j = row_ptr[i]; j < row_ptr[i+1]; j++)
                {
                    Ax_k_1[i] = Ax_k_1[i] + val[j]*x_k_1[col_idx[j]];
                }
                x_k[i] = d_term + d * Ax_k_1[i];
            }
            }
            
            
            

            /* Check stopping criterion */
            
            
            #pragma omp parallel for schedule(dynamic) reduction(+:err) reduction(max: max_err)
            for (i = 0; i < N; i++)
            {
                err += fabs(x_k[i]-x_k_1[i]);
                #pragma omp critical 
                {
                if (err > max_err){
                    
                    max_err = err;
                }
                }
            }

            if (max_err < epsilon){
                break;
            }
            

            /* Updating vectors if continue*/
            #pragma omp for schedule(dynamic)
            for (i = 0; i < N; i++)
            {
                x_k_1[i] = x_k[i];
            }
            
        
            #pragma omp critical
            k += 1;
        }

    
    
    memcpy(scores, x_k, N*sizeof(double));
    printf("Last iteration: %d, Max error: %f, epsilon: %f\n", k, max_err, epsilon);
    printf("\n");
    
    
    

    free(x_k_1);
    free(x_k);
    free(Ax_k_1);
    free(non_zero_columns);
    free(dong_index);
    
}   