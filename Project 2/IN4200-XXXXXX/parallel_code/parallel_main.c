#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../simple-jpeg/import_export_jpeg.h"
#include "../utilities/functions.h"
#include "../utilities/functions_parallel.h"



int main(int argc, char** argv) {
    int m, n, c, iters;
    int my_m, my_n, my_rank, num_procs, total;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars, *my_image_chars, *image_chars1;
    char *input_jpeg_filename, *output_jpeg_filename;
    
    

    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_file name */
    kappa = atof(argv[1]); 
    iters = atoi(argv[2]); 
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &num_procs);

    

    

    if (my_rank==0) {
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
        //import_JPEG_file(input_jpeg_filename, &image_chars1, &m, &n, &c);
        //allocate_image (&whole_image, m, n);

        
    }
    image_chars1 = malloc(m*n*sizeof(*image_chars1)+1);
    

    MPI_Bcast (&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //MPI_Bcast (&kappa, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    //MPI_Bcast (&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);


    //int rest = m%num_procs;
    //int count = m / num_procs;
    //int start, stop;

    

    my_n = n;
    
    my_m = m/num_procs + (my_rank <= m%num_procs-1);

    

    printf("%d\n", my_m);
    MPI_Barrier(MPI_COMM_WORLD);

    total = my_n*my_m;

    
    int *n_rows = malloc(num_procs*sizeof(*n_rows)+1);
    
    for (int i = 0; i < num_procs; i++) n_rows[i] = 0;
    
    
    MPI_Gather(&total, 1, MPI_INT, &n_rows[my_rank], 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    /* 2D decomposition of the m x n pixels evenly among the MPI processes */
    MPI_Bcast(&n_rows, num_procs, MPI_INT, 0, MPI_COMM_WORLD);
    

    int *displs = malloc(num_procs*sizeof *displs+1);

    MPI_Barrier(MPI_COMM_WORLD);
    printf("h1\n");
    MPI_Barrier(MPI_COMM_WORLD);
    
    displs[0] = 0;
    for (int rank = 0; rank < num_procs-1; rank++) {
        //n_rows[rank] = total;
    
        displs[rank+1] = displs[rank] + n_rows[rank];
    
    }

    MPI_Barrier(MPI_COMM_WORLD);
    printf("h2\n");
    MPI_Barrier(MPI_COMM_WORLD);

    // Last remainder processes gets an extra row.
    
    //n_rows[num_procs-1] = total;
    MPI_Barrier(MPI_COMM_WORLD);

    if (my_rank==0){
        for (int i= 0; i< num_procs; i++) printf("col with rank %d is %d\n", i, n_rows[i]);
    }
    
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    
    my_image_chars = malloc(total*sizeof(*my_image_chars)+1);

    
    
    allocate_image (&u, my_m, my_n);
    allocate_image (&u_bar, my_m, my_n);
    /* each process asks process 0 for a partitioned region */
    /* of image_chars and copy the values into u */
    /* ... */

    

    MPI_Scatterv(image_chars, 
                n_rows, 
                displs, 
                MPI_UNSIGNED_CHAR, 
                my_image_chars , 
                total, 
                MPI_UNSIGNED_CHAR, 
                0, 
                MPI_COMM_WORLD);
        
    MPI_Barrier(MPI_COMM_WORLD);
    printf("h3\n");
    MPI_Barrier(MPI_COMM_WORLD);

    convert_jpeg_to_image (my_image_chars, &u);
    MPI_Barrier(MPI_COMM_WORLD);
    
    iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters, my_rank, num_procs);

    

    /* each process sends its resulting content of u_bar to process 0 */
    /* process 0 receives from each process incoming values and */
    /* copy them into the designated region of struct whole_image */
    convert_image_to_jpeg(&u_bar, my_image_chars);
    if (my_image_chars){
        printf("Rank %d is Null\n", my_rank);
    } else{
        printf("Rank %d not Null\n", my_rank);
    }
    

    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Gatherv(my_image_chars, 
                total, 
                MPI_UNSIGNED_CHAR, 
                image_chars1, 
                n_rows, 
                displs, 
                MPI_UNSIGNED_CHAR, 
                0, 
                MPI_COMM_WORLD);
    
    if (my_rank==0) {
        //convert_image_to_jpeg(&whole_image, image_chars1);
        export_JPEG_file(output_jpeg_filename, image_chars1, m, n, c, 75);
        
        free(my_image_chars); 
        free(image_chars1);
        free(image_chars);
        free(n_rows);
    }
    else{
        free(my_image_chars);
        free(image_chars1);
        free(n_rows);
    }
  
    
    deallocate_image (&u);
    deallocate_image (&u_bar);
    free(displs); 
    //free(n_rows);
    MPI_Finalize ();

    
    return 0;

}