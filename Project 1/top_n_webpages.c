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
    int r =N%2 - 1; // Used in the even step.
    for (size_t i = 0; i <N; i++) {
        if (i%2 == 1) {
            for (size_t j = 0; j <N/2; j++) {
                compare_exchange(&scores[2*j], &scores[2*j+1], &score_web_page_num[2*j], &score_web_page_num[2*j+1]);
            }
        } else {
            for (size_t j = 0; j <N/2 + r; j++) {
                compare_exchange(&scores[2*j+1], &scores[2*j+2], &score_web_page_num[2*j+1], &score_web_page_num[2*j+2]);
            }
        }
    }
    

    /* Print top n webpages */

    printf("------------------------------------------\n");
    printf("------------ Top %d webpages ------------\n", n);
    printf("------------------------------------------\n");
    
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

