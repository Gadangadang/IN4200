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
    double tmp[N];
    int tmp2[N];
    //sort(scores, score_web_page_num, N);
    mergesortV2(scores, N, tmp, score_web_page_num, tmp2);

    /* Print top n webpages */

    printf("------------------------------------------\n");
    printf("             Top %d webpages              \n", n);
  
    
    for (size_t i = 0; i <n; i++)
    {   
        printf("Rank: %ld  | Score: %f | Webpage nr: %d\n", i+1, scores[N-i-1], score_web_page_num[N-i-1]);
    }
    



    free(score_web_page_num);
   
 }




void merge(double *X, int n, double *tmp, int *Y, int *tmp2)
{
    int i = 0;
    int j = n / 2;
    int ti = 0;
    //i will iterate till first  half anf J will iterate for 2nd half of array
    while (i < n / 2 && j < n)
    {
        if (X[i] < X[j])
        {
            tmp[ti] = X[i];
            tmp2[ti] = Y[i];
            ti++;
            i++;
        }
        else
        {
            tmp[ti] = X[j];
            tmp2[ti] = Y[j];
            ti++;
            j++;
        }
    }
    while (i < n / 2)
    { /* finish up lower half */
        tmp[ti] = X[i];
        tmp2[ti] = Y[i];
        ti++;
        i++;
    }
    while (j < n)
    { /* finish up upper half */
        tmp[ti] = X[j];
        tmp2[ti] = Y[j];
        ti++;
        j++;
    }
    //Copy sorted array tmp back to  X (Original array)
    memcpy(X, tmp, n * sizeof(double));
    memcpy(Y, tmp2, n*sizeof(int));

} // end of merge()

void mergesortV2(double *X, int n, double *tmp, int *Y, int *tmp2)
{
    if (n < 2)
        return;

#pragma omp task firstprivate(X, n, tmp, Y, tmp2)
    mergesortV2(X, n / 2, tmp, Y, tmp2);

#pragma omp task firstprivate(X, n, tmp, Y, tmp2)
    mergesortV2(X + (n / 2), n - (n / 2), tmp, Y + (n / 2), tmp2);

//Wait for both paralel tasks to complete execution
#pragma omp taskwait

    /* merge sorted halves into sorted list */
    merge(X, n, tmp, Y, tmp2);
}
