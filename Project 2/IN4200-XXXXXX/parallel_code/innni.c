if (my_rank == 0){
        int start_index = my_m*my_n*sizeof(char);
        
        int my_other_rank = count;
        printf("Total length %ld\n", m*n*sizeof(char));
        printf("Rank 0 m: %ld\n", my_n*my_m*sizeof(char));
        printf("Rank other m: %ld\n\n", my_other_rank*my_n*sizeof(char));
        printf("Rest space: %ld\n", m*n*sizeof(char) -my_n*my_m*sizeof(char) - 3*my_other_rank*my_n*sizeof(char) );
        
        strncpy(my_image_chars, image_chars, my_n*my_m*sizeof(char));
        printf("Rank 0 allocating done\n");
        int array_length = my_n*my_other_rank*sizeof(char);

        for (int i = 1; i < num_procs; i++){
            
            
            MPI_Send(&image_chars[start_index], array_length, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Rank %d allocating done\n", i);
            start_index += array_length;
            
        }
    } else {
        MPI_Recv(&my_image_chars, my_n*my_m*sizeof(char), MPI_CHAR, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    }