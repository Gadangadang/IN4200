#include "functions.h"
#include <stdlib.h>
#include <stdio.h>



void deallocate_image(image *u){
    free(*u->image_data);
}

void allocate_image(image *u, int m, int n){
    u->image_data = malloc(m*sizeof(float));
    for (int i= 0; i < m; i++){
        u->image_data[i] = malloc(n*sizeof(float));
        for (int j = 0; j < n; j++){
            *u->image_data[i,j] = (float) 2.;
        }
    }

    for (int i= 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%f",*u->image_data[i,j]);
        }
        printf("\n");
    }
}


void convert_jpeg_to_image(const unsigned char* image_chars, image *u){
    
}
void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    
}
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){
    
}