#ifndef FUNCTIONS_PARALLEL_H   /* Include guard */
#define FUNCTIONS_PARALLEL_H
#include "image.h"



void iso_diffusion_denoising_parallel(image *u, image u_bar, double kappa, int iters);


#endif // FUNCTIONS_PARALLEL