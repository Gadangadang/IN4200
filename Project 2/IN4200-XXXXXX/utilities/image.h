#ifndef IMAGE_H   /* Include guard */
#define IMAGE_H


typedef struct
{
float** image_data; /* a 2D array of floats */
int m; /* # pixels in vertical-direction */
int n; /* # pixels in horizontal-direction */
}
image;




#endif // FUNCTIONS_PARALLEL