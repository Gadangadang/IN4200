

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){
    int state = 1;

    int k = 1;
    
    double *x_k_1 = scores;
    double *x_k = (double*)malloc(N*sizeof(double));
    double max_err = 0;
    double W_k_1;
    double d_term;

    while (state == 1){
        

        /* Calculate W_k_1 */

        W_k_1 = 0;
        
        d_term = (1-d+d*W_k_1)/(N);
        

        /* Sparse matrix multiplication */

        double *Ax_k_1 = (double*)malloc(N*sizeof(double));
        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = row_ptr[i]; j < row_ptr[i+1]; j++)
            {
                Ax_k_1[i] = Ax_k_1[i] + val[j]*x_k_1[col_idx[j]];
            }
            
        }
        

        /* Finding x_k */

        for (size_t i = 0; i < N; i++)
        {
            x_k[i] = d_term + d*Ax_k_1[i];
        }


        /* Check stopping criterion */

        
        for (size_t i = 0; i < N; i++)
        {
            
        }
        

        /* Updating vectors */
        
        memcpy(x_k, x_k_1, N*sizeof(double));

        k += 1;
        

        
    }

    
}   