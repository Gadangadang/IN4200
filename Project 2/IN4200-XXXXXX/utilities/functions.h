#ifndef FUNCTIONS_H   /* Include guard */
#define FUNCTIONS_H
#include "image.h"




void deallocate_image(image *u);
void deallocate_image(image *u_bar);
void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);

#endif // FUNCTIONS