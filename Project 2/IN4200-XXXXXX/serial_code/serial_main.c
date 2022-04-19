#include <stdio.h>
#include "../simple-jpeg/import_export_jpeg.h"
#include "../utilities/functions.h"
#include "../utilities/image.h"

int main(int argc, char **argv){
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;
    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename */
    /* ... */
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    allocate_image (&u, m, n);
    allocate_image (&u_bar, m, n);
    convert_jpeg_to_image (image_chars, &u);
    iso_diffusion_denoising (&u, &u_bar, kappa, iters);
    convert_image_to_jpeg (&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
    deallocate_image (&u);
    deallocate_image (&u_bar);
return 0;
}


void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);