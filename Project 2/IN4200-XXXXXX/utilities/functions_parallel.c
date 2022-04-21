#include "functions_parallel.h"
#include "functions.h"



void iso_diffusion_denoising_parallel(image *u, image *u_bar, double kappa, int iters, int rank, int num_procs){
    int m = u->m;
    int n = u->n;
    image *tmp;
    float *upper_buff = malloc(m*sizeof(*upper_buff)); 
    float *lowerbuff = malloc(m*sizeof(*lowerbuff));

    /* Corners not changing so just copy from beginning */

    for (int i =0; i < m; i++) memcpy(u_bar->image_data[i], u->image_data[i], n*sizeof(float) );

    MPI_Barrier(MPI_COMM_WORLD);


    for (int iter = 0; iter < iters; iter ++){
        MPI_Status status;

        /* Each part needs to send its border to the neighboring partner */

        if (my_rank == 0){
            MPI_Send(&u->image_data[m-1], n, MPI_FLOAT, &lowerbuff, 0, MPI_COMM_WORLD);
            MPI_Recv(&upper_buff, n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, status);

        } else if (my_rank %2 != 0 & my_rank != num_procs-1){
            MPI_Recv(&lowerbuff, n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, status);
            MPI_Recv(&upper_buff, n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, status);
            MPI_Send(&u->image_data[0], n, MPI_FLOAT, &upper_buff, 0, MPI_COMM_WORLD);
            MPI_Send(&u->image_data[m-1], n, MPI_FLOAT, &lowerbuff, 0, MPI_COMM_WORLD);

        } else if (my_rank % 2 == 0 & my_rank != 0 & my_rank != num_procs-1) {
            
            MPI_Send(&u->image_data[0], n, MPI_FLOAT, &upper_buff, 0, MPI_COMM_WORLD);
            MPI_Send(&u->image_data[m-1], n, MPI_FLOAT, &lowerbuff, 0, MPI_COMM_WORLD);
            MPI_Recv(&upper_buff, n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD, status);
            MPI_Recv(&lowerbuff, n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD, status);
            

        } else if (my_rank == num_procs-1) {
            
            MPI_Recv(&lowerbuff, n, MPI:FLOAT, my_rank-1, 0, MPI_COMM_WORLD, status);
            MPI_Send(&u->image_data[0], n, MPI_FLOAT, &upper_buff, 0, MPI_COMM_WORLD);
           
        }
        
        /* Calculate interior points */
        for (int i = 1; i < m-1; i++){
            for (int j = 1; j < n-1; j++){
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa*( u->image_data[i-1][j] 
                                                                      + u->image_data[i][j-1] 
                                                                      - 4*u->image_data[i][j] 
                                                                      + u->image_data[i][j+1] 
                                                                      + u->image_data[i+1][j] );

            }
        }

        /*  */



        MPI_Barrier(MPI_COMM_WORLD);
        tmp = u;
        u = u_bar;
        u_bar = tmp;
    }
}