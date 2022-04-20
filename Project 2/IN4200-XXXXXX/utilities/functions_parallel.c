#include "functions_parallel.h"
#include "functions.h"



void iso_diffusion_denoising_parallel(image *u, image *u_bar, double kappa, int iters){
    int m = u->m;
    int n = u->n;
    image *tmp;

    /* Corners not changing so just copy from beginning */

    for (int i =0; i < m; i++) memcpy(u_bar->image_data[i], u->image_data[i], n*sizeof(float) );


    for (int iter = 0; iter < iters-1; iter ++){
        
        for (int i = 1; i < m-1; i++){
            for (int j = 1; j < n-1; j++){
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa*( u->image_data[i-1][j] + u->image_data[i][j-1] - 4*u->image_data[i][j] +u->image_data[i][j+1] +u->image_data[i+1][j] );

            }
        }

        tmp = u;
        u = u_bar;
        u_bar = tmp;

    }
    for (int i = 1; i < m-1; i++){
            for (int j = 1; j < n-1; j++){
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa*( u->image_data[i-1][j] + u->image_data[i][j-1] - 4*u->image_data[i][j] +u->image_data[i][j+1] +u->image_data[i+1][j] );

            }
        }
}