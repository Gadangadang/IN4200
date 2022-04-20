#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void deallocate_image(image *u){
    int m = u->m;

    for (int i = 0; i < m; i++){
        free(u->image_data[i]);
    }
    free(u->image_data);
}

void allocate_image(image *u, int m, int n){
    u->n = n;
    u->m = m;
    u->image_data = malloc(m*sizeof(float*));
    for (int i= 0; i < m; i++){
        
        u->image_data[i] = malloc(n*sizeof(float)) ;
        
    }    
}


void convert_jpeg_to_image(const unsigned char* image_chars, image *u){
    int m = u-> m;
    int n = u-> n;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            u->image_data[i][j] = (float) image_chars[i*n + j];
        }
    } 
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    int m = u-> m;
    int n = u-> n;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            image_chars[i*n + j] = (unsigned char) u->image_data[i][j];
        }
    }
    
}
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){
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