#include <math.h>

void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){
    int state = 1;

    int k = 0;
    
    double *x_k_1 = malloc(N*sizeof(double));

    memcpy(x_k_1, scores, N*sizeof(double));
    
    double *x_k = malloc(N*sizeof(double));
    double *Ax_k_1 = malloc(N * sizeof(double));
    double max_err; 
    double err, W_k_1, d_term;

    while (state == 1){
       max_err=0;
       err = 0;

       for (size_t i = 0; i < N; i++)
       {
           Ax_k_1[i] = 0 ;
       }
       

        /* Calculate W_k_1 */

        W_k_1 = 0;
        
        d_term = (1-d+d*W_k_1)/(N);
        

        /* Sparse matrix multiplication */

        
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
            x_k[i] = d_term + d * Ax_k_1[i];
        }


        /* Check stopping criterion */
        max_err += fabs(x_k[0] - x_k_1[0]);
        printf("\n");
        printf("%d\n", k);
        printf("max_err = %f, epsilon = %f\n", max_err, epsilon);
        for (size_t i = 1; i < N; i++)
        {
            err += fabs(x_k[i]-x_k_1[i]);
            
            if (err > max_err){
                max_err = err;
            }
        }

        
        printf("max_err = %f, epsilon = %f\n", max_err, epsilon);

        if (max_err < epsilon){
            break;
        }
        

        /* Updating vectors */

        for (size_t i = 0; i < N; i++)
        {
            x_k_1[i] = x_k[i];
        }
        


        if (k == 10){
            break;
        }

        k += 1;
        }

    
    memcpy(scores, x_k, N*sizeof(double));
    

    for (int i = 0; i < N; ++i)
        printf("x_k: %f and score: %f\n", x_k[i], scores[i]);

    free(x_k_1);
    free(x_k);
    free(Ax_k_1);

    
}   