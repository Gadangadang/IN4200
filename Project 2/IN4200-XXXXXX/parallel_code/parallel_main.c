#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../simple-jpeg/import_export_jpeg.h"
#include "../utilities/functions.h"
#include "../utilities/functions_parallel.h"



int main(int argc, char** argv) {
    int m, n, c, iters;
    int my_m, my_n, my_rank, num_procs;
    float kappa;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars, *image_chars1;
    char *input_jpeg_filename, *output_jpeg_filename;
    
    int root_rank = 0;

    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_file name */
    kappa = atof(argv[1]); iters = atoi(argv[2]); 
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    

    

    if (my_rank==0) {
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        import_JPEG_file(input_jpeg_filename, &image_chars1, &m, &n, &c);
        allocate_image (&whole_image, m, n);

        
    }
    

    MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);


    int rest = m%num_procs;
    int count = m / num_procs;
    int start, stop;
    
    
    

    /* 2D decomposition of the m x n pixels evenly among the MPI processes */
    
    int *n_cols = malloc(num_procs*sizeof *n_cols);
    int *displs = malloc(num_procs*sizeof *displs);

    int cols = m/num_procs;
    int remainder = m%num_procs;

    // Last remainder processes gets an extra row.
    displs[0] = 0;
    for (int rank = 0; rank < num_procs-1; rank++) {
        n_cols[rank] = cols + ((rank >= (num_procs - remainder)) ? 1:0);
        
        displs[rank+1] = displs[rank] + n_cols[rank];
        
    }
    n_cols[num_procs-1] = cols + ((num_procs-1) >= (num_procs - remainder) ? 1:0);

    

    my_n = n;
    
    my_m = n_cols[my_rank];

    int total = my_n*my_m;
    
    my_image_chars = malloc(total*sizeof(char));
    
    allocate_image (&u, my_m, my_n);
    allocate_image (&u_bar, my_m, my_n);
    /* each process asks process 0 for a partitioned region */
    /* of image_chars and copy the values into u */
    /* ... */

    
    
    MPI_Scatterv(image_chars, n_cols, displs, MPI_UNSIGNED_CHAR, my_image_chars , total*sizeof(char), MPI_UNSIGNED_CHAR, root_rank, MPI_COMM_WORLD);
        
    

    convert_jpeg_to_image (my_image_chars, &u);
    MPI_Barrier(MPI_COMM_WORLD);
    
    //iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);

    /* each process sends its resulting content of u_bar to process 0 */
    /* process 0 receives from each process incoming values and */
    /* copy them into the designated region of struct whole_image */
    convert_image_to_jpeg(&u_bar, my_image_chars);
    
    
    MPI_Gatherv(my_image_chars, n_cols[my_rank], MPI_UNSIGNED_CHAR, image_chars, n_cols, displs, MPI_UNSIGNED_CHAR, root_rank, MPI_COMM_WORLD);
    
    if (my_rank==0) {
        //convert_image_to_jpeg(&whole_image, image_chars1);
        export_JPEG_file(output_jpeg_filename, image_chars1, m, n, c, 75);
        deallocate_image (&whole_image);
        free(my_image_chars); 
        free(image_chars1);
        free(image_chars);
    }
    else{
        free(my_image_chars);
    }
  
    
    deallocate_image (&u);
    deallocate_image (&u_bar);
    MPI_Finalize ();

    free(n_cols); free(displs); 
    return 0;

}