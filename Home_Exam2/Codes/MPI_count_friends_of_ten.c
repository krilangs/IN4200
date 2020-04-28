int MPI_count_friends_of_ten(int M, int N, int** v)
{
    /* Count the total number of "triple-friends of 10"
       inside a 2D array of dimension MxN.
       Input:
       * M : Number of rows.
       * N : Number of columns.
       * v : 2D array of dimension MxN.
    */
    int size, rank, *buffer=NULL;
    int local_friends = 0, tot_friends = 0;
    int remaining_rows = 0; // Number of remaining rows.
    int remainder_idx = 0;  // Start index of remaining elements.
    int rows = M;
    int columns = N;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&columns, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int elems_calc = rows*columns/size - (rows*columns/size)%columns;
    int elems_send = elems_calc + 2*columns;

    if (rank==0){
        printf("Elements to calculate: %d\n", elems_calc);
        printf("Elements to send: %d\n", elems_send);
    }

    else
        buffer = calloc(elems_send, sizeof(int));

    for (int i=1; i<size; i++){
        if (rank==0){
            MPI_Send(&(v[0][(i-1)*elems_calc]), elems_send, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        if (rank==i){
            MPI_Recv(buffer, elems_send, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    if (rank!=0){
        local_friends = count_MPI(elems_send/columns-2, columns, buffer, true);
    }


    if (rank==0){
        if (size==1)
            remainder_idx = 0;
        else
            remainder_idx = elems_calc*(size-1);

        remaining_rows = (rows*columns - remainder_idx)/columns;
        local_friends = count_MPI(remaining_rows, columns, &(v[0][remainder_idx]), false);
    }

    MPI_Allreduce(&local_friends, &tot_friends, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    free(buffer);

    return tot_friends;
}
