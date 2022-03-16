#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
 
 
 void top_n_webpages(int N, double *scores, int n){
     printf("\n");
    
    /* Create a hold vector to keep track of webpage nr */
    int *score_web_page_num = malloc(N*sizeof(int));
    
    #pragma omp parallel for
    for (size_t i = 0; i < N; i++)
    {
        score_web_page_num[i] = i;
    }   

    /* sort the score array and the webpage vector */
    
    sort(scores, score_web_page_num, N);

    /* Print top n webpages */

    printf("------------------------------------------\n");
    printf("             Top %d webpages              \n", n);
  
    
    for (size_t i = 0; i <n; i++)
    {   
        printf("Rank: %ld  | Score: %f | Webpage nr: %d\n", i+1, scores[N-i-1], score_web_page_num[N-i-1]);
    }
    



    free(score_web_page_num);
   
 }



int compare_exchange(double *a, double *b, int *c, int *d){
    double tmp;
    int tmp2;
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;

        tmp2 = *c;
        *c = *d;
        *d = tmp2;
        return 1;
    }
    return 0;
}

int sort(double *a, int *b, int N){
    int r =N%2 - 1; // Used in the even step.
    int change_even = 0;
    int change_odd = 0;
    #pragma omp parallel if (N > 1500)
    {
        for (size_t i = 0; i <N; i++) {
            #pragma omp for reduction(+:change_odd)
            for (size_t j = 0; j <N/2; j++) {
                if(compare_exchange(&a[2*j], &a[2*j+1], &b[2*j], &b[2*j+1])){
                    change_odd = 1;
                }
            }
            #pragma omp for reduction(+:change_even)
            for (size_t j = 0; j <N/2 + r; j++) {
                if(compare_exchange(&a[2*j+1], &a[2*j+2], &b[2*j+1], &b[2*j+2])){
                    change_even = 1;
                }
            }

            if (!change_even && !change_odd){
                break;
            }
            #pragma omp barrier
            #pragma omp single
            {
                change_even = change_odd = 0;
            }
            
        }
    }
    return 0;
}