#include "functions_parallel.h"
#include "functions.h"



void iso_diffusion_denoising_parallel(image *u, image *u_bar, double kappa, int iters, int rank, int num_procs){
    int m = u->m;
    int n = u->n;
    image *tmp;
    float *upper_buff = malloc(n*sizeof(*upper_buff)+1); 
    float *lowerbuff = malloc(n*sizeof(*lowerbuff)+1);

    /* Corners not changing so just copy from beginning */

    for (int i =0; i < m; i++) memcpy(u_bar->image_data[i], u->image_data[i], n*sizeof(float) );

    MPI_Barrier(MPI_COMM_WORLD);


    for (int iter = 0; iter < iters; iter ++){
        MPI_Status status;

        /* Each part needs to send its border to the neighboring partner */

        if (rank == 0){
            MPI_Send(u->image_data[m-1], n, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD);
            MPI_Recv(upper_buff, n, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);

        } else if (rank %2 != 0 & rank != num_procs-1){
            MPI_Recv(lowerbuff, n, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(upper_buff, n, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(u->image_data[0], n, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD);
            MPI_Send(u->image_data[m-1], n, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD);

        } else if (rank % 2 == 0 & rank != 0 & rank != num_procs-1) {
            
            MPI_Send(u->image_data[0], n, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD);
            MPI_Send(u->image_data[m-1], n, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD);
            MPI_Recv(upper_buff, n, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(lowerbuff, n, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
            

        } else if (rank == num_procs-1) {
            
            MPI_Recv(lowerbuff, n, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(u->image_data[0], n, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD);
           
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

        /* Make sure the border points for the given chunks are calculated too */

        if (rank == 0){ // Only bottom part taken to account
            for (int j = 1; j < n-1; j++){
                u_bar->image_data[m-1][j] = u->image_data[m-1][j] + kappa*( u->image_data[m-2][j] 
                                                                          + u->image_data[m-1][j-1] 
                                                                          - 4*u->image_data[m-1][j] 
                                                                          + u->image_data[m-1][j+1] 
                                                                          + upper_buff[j] );
        }

        } else if (rank == num_procs-1) { // Only top part taken to account
            for (int j = 1; j < n-1; j++){
                u_bar->image_data[0][j] = u->image_data[0][j] + kappa*( lowerbuff[j] 
                                                                      + u->image_data[0][j-1] 
                                                                      - 4*u->image_data[0][j] 
                                                                      + u->image_data[0][j+1] 
                                                                      + u->image_data[1][j] );
        }

        } else { // Both top and bottom part taken to account
            for (int j = 1; j < n-1; j++){
                u_bar->image_data[0][j] = u->image_data[0][j] + kappa*( lowerbuff[j] 
                                                                      + u->image_data[0][j-1] 
                                                                      - 4*u->image_data[0][j] 
                                                                      + u->image_data[0][j+1] 
                                                                      + u->image_data[1][j] );

                u_bar->image_data[m-1][j] = u->image_data[m-1][j] + kappa*( u->image_data[m-2][j] 
                                                                          + u->image_data[m-1][j-1] 
                                                                          - 4*u->image_data[m-1][j] 
                                                                          + u->image_data[m-1][j+1] 
                                                                          + upper_buff[j] );
        }

        }
        
        MPI_Barrier(MPI_COMM_WORLD);
        tmp = u;
        u = u_bar;
        u_bar = tmp;
    }
    free(upper_buff);
    free(lowerbuff);
}