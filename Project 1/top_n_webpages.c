#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
 
 
 void top_n_webpages(int N, double *scores, int n){
     /* Print top n webpages */

    /* Create vector with webpage id in increasing order */

    int *webpage_vec = malloc(N*sizeof(int));
    int *perm = malloc(N*sizeof(int));

    //scores[4] = 0.5;

    for (size_t i = 0; i < N; i++)
    {
        webpage_vec[i] = i;
        perm[i] = i;
    }
    
    //sort(scores, perm, 0, N);

    printf("   ----------------\n");
    printf("    Top %d webpages \n", n);
    for (size_t i = 0; i < n; i++){
        printf("Webpage: %d, score: %f\n", webpage_vec[perm[i]], scores[perm[i]]);
    }


    free(webpage_vec); free(perm);
 }


#define SWAP(a, b) int t=*a; *a=*b; *b=t;

void sort(int arr[], int perm[], int beg, int end)
{
    if (end > beg + 1) {
        int piv = arr[perm[beg]], l = beg + 1, r = end;
        while (l < r) {
            if (arr[perm[l]] <= piv)
                l++;
            else
            {
                SWAP(&perm[l], &perm[--r]);
            }
        }
        SWAP(&perm[--l], &perm[beg]);
        sort(arr, perm, beg, l);
        sort(arr, perm, r, end);
    }
}