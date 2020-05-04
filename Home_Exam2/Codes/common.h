#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void generate_known_2d_array(int ***v)
{   /*
    Parameters
    ----------
    v : int triple pointer
        Address of un-initialized 2D array.
    */
    int test_data[] = {1, 5, 6, 3, 1,
                       2, 4, 4, 1, 7,
                       7, 2, 3, 1, 2,
                       3, 2, 2, 5, 3};

    int M_tmp = 4; // Rows.
    int N_tmp = 5; // Columns.
    int **v_tmp;

    // Allocating row-major contiguous 2D array.
    v_tmp = malloc(M_tmp*sizeof(int*));
    v_tmp[0] = calloc(M_tmp*N_tmp, sizeof(int));

    for (int i = 1; i < M_tmp; i++)
        v_tmp[i] = &(v_tmp[0][i*N_tmp]);

    // Inserting data.
    for (int i = 0; i < M_tmp*N_tmp; i++)
        v_tmp[0][i] = test_data[i];

    *v = v_tmp;
}

void generate_random_2d_array(int M, int N, int ***v){
    /*
       Parameters
       ----------
       M : integer
           The number of row elements.
       N : integer
           The number of column elements.
       v : int triple pointer
           Address of un-initialized 2D array.
       */
       int **v_tmp;

       // Allocating row-major contiguous 2D array.
       v_tmp = malloc(M*sizeof(int*));
       v_tmp[0] = calloc(M*N, sizeof(int));

       for (int i = 1; i < M; i++)
           v_tmp[i] = &(v_tmp[0][i*N]);

       // Inserting data.
       for (int i = 0; i < M*N; i++)
           v_tmp[0][i] = rand()%10;

       *v = v_tmp;
}

int count_MPI(int M, int N, int *v, bool extend_bottom_rows){
    /*
        Find the number of triple friends of 10.
        Use indexing of the underlying 1D array.
        Parameters
        ----------
        M : integer
            Number of row elements.
        N : integer
            Number of column elements.
        v : int pointer
            2D array flattened to a 1D array. Indexed by v[row][col] =
            v[row*N + col].
        extend_bottom_rows : bool
            For toggling calculation of vertical, diagonal, and anti-
            diagonal on / off for the two last rows of the array. This is
            turned on (true) when a sub-matrix which does not include the
            final two rows of the full matrix, is passed to this function,
            since the last two rows of the sub-matrix isn't actually the
            two final rows of the full matrix.  Hence the vertical,
            diagonal, and anti-diagonal must be calculated in addition to
            the horizontal for all rows.
    */
    int row, col, extension;
    int friends = 0;

    if (extend_bottom_rows){
        extension = 2;
    }
    else{
        extension = 0;
    }

    for (row=0; row<M-2+extension; row++){
        // First column.
        // Horizontal.
        if ((v[row*N] + v[row*N + 1] + v[row*N + 2]) == 10) friends++;
        // Vertical.
        if ((v[row*N] + v[(row + 1)*N] + v[(row + 2)*N]) == 10) friends++;
        // Diagonal.
        if ((v[row*N] + v[(row + 1)*N + 1] + v[(row + 2)*N + 2]) == 10) friends++;

        // Second column.
        // Horizontal.
        if ((v[row*N + 1] + v[row*N + 2] + v[row*N + 3]) == 10) friends++;
        // Vertical.
        if ((v[row*N + 1] + v[(row + 1)*N + 1] + v[(row + 2)*N + 1]) == 10) friends++;
        // Diagonal.
        if ((v[row*N + 1] + v[(row + 1)*N + 2] + v[(row + 2)*N + 3]) == 10) friends++;

        for (col = 2; col < N-2; col++){
            // Horizontal.
            if ((v[row*N + col] + v[row*N + col + 1] + v[row*N + col + 2]) == 10) friends++;
            // Vertical.
            if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
            // Diagonal.
            if ((v[row*N + col] + v[(row + 1)*N + col + 1] + v[(row + 2)*N + col + 2]) == 10) friends++;
            // Anti-diagonal.
            if ((v[row*N + col] + v[(row + 1)*N + col - 1] + v[(row + 2)*N + col - 2]) == 10) friends++;
        }

        // Manual handling for the last two columns, only vertical and anti-diagonal calculated.
        // Vertical.
        if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
        // Anti-diagonal.
        if ((v[row*N + col] + v[(row + 1)*N + col - 1] + v[(row + 2)*N + col - 2]) == 10) friends++;
        col++;    // Advancing to the last column.
        // Vertical.
        if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
        // Anti-diagonal.
        if ((v[row*N + col] + v[(row + 1)*N + col - 1] + v[(row + 2)*N + col - 2]) == 10) friends++;
    }

    if (!extend_bottom_rows){
        /* Manual handling for the last two rows if they are the final two
         * rows of the full matrix / 2D array. Only horizontal calculated.
        */
        for (col = 0; col < N-2; col++){
            if ((v[row*N + col] + v[row*N + col + 1] + v[row*N + col + 2]) == 10) friends++;
        }
        row++;    // Advancing to the last row.
        for (col = 0; col < N-2; col++){
            if ((v[row*N + col] + v[row*N + col + 1] + v[row*N + col + 2]) == 10) friends++;
        }
    }

    return friends;
}

#endif // COMMON_H
