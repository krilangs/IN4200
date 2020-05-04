#include <mpi.h>
#include "common.h"
#include "MPI_count_friends_of_ten.c"

int main (int argc, char **argv)
{
    int M, N, rank, size, num_triple_friends;
    int **v = NULL;
    double time_generate = 0, time_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank==0) {
        // Decide the values for M and N
        N = atoi(argv[1]);  // Columns
        M = atoi(argv[2]);  // Rows
        printf("2D array dimension: %ix%i\n", M, N);
        printf("Total number of processors: %d\n", size);

        // Allocate 2D array v and assign it with suitable values
        double start_generate = MPI_Wtime();
        generate_random_2d_array(M, N, &v);
        double stop_generate = MPI_Wtime();
        time_generate = stop_generate - start_generate;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double start_count = MPI_Wtime();
    if (rank==0)
        num_triple_friends = MPI_count_friends_of_ten(M, N, v);
    else
        num_triple_friends = MPI_count_friends_of_ten(0, 0, NULL);

    MPI_Barrier(MPI_COMM_WORLD);

    double stop_count = MPI_Wtime();
    time_count = stop_count - start_count;

    if (rank==0){
        printf("MPI rank <%d>: Number of triple friends = %d\n", rank, num_triple_friends);
        printf("2D array generated in: %f s\n", time_generate);
        printf("Time calculating friends of 10: %f s\n", time_count);
    }

    if (rank==0){
        // Deallocation of 2D array v
        free(v[0]);
        free(v);
    }

    MPI_Finalize();

    return 0;
}
