#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void generate_known_2d_array(int ***v)
{
    /* Allocate and fill a 2D array of dimension MxN with known
       values to be used as a test for the count triple-friends
       of 10 function.
       Input:
       * v : Address of un-initialized 2D array of dimension MxN.
    */
    int test_data[] = {1, 5, 6, 3, 1,
                       2, 4, 4, 1, 7,
                       7, 2, 3, 1, 2,
                       3, 2, 2, 5, 3};

    int M_tmp = 4;  // Rows.
    int N_tmp = 5;  // Columns.
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

void generate_random_2d_array(int M, int N, int ***v)
{
    /* Allocate and fill a 2D array of dimension MxN with randomly
       generated numbers.
       Input:
       * M : Number of rows.
       * N : Number of columns.
       * v : Address of un-initialized 2D array of dimension MxN.
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

int count_MPI(int M, int N, int *v, bool extend_rows)
{
    /* Count the total number of triple friends of 10 for the MPI
       parallelized function. Use indexing of the underlying 1D array.
       Input:
       * M : Number of rows.
       * N : Number of columns.
       * v : 2D array dimension MxN flattened to a 1D array.
       * extend_rows : For toggling calculation for the two last rows of the array.
    */
    int row, col, extend;
    int friends = 0;

    if (extend_rows){
        extend = 2;
    }
    else{
        extend = 0;
    }

    for (row = 0; row < M-2+extend; row++){
        // First two columns.
        for (int col = 0; col < 2; col++){
            if ((v[row*N + col] + v[row*N + (col + 1)] + v[row*N + (col + 2)]) == 10) friends++;
            // Vertical.
            if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
            // Diagonal.
            if ((v[row*N + col] + v[(row + 1)*N + (col + 1)] + v[(row + 2)*N + (col + 2)]) == 10) friends++;
        }

        for (col = 2; col < N-2; col++){
            // Horizontal.
            if ((v[row*N + col] + v[row*N + col + 1] + v[row*N + col + 2]) == 10) friends++;
            // Vertical.
            if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
            // Backward diagonal.
            if ((v[row*N + col] + v[(row + 1)*N + col - 1] + v[(row + 2)*N + col - 2]) == 10) friends++;
            // Diagonal.
            if ((v[row*N + col] + v[(row + 1)*N + col + 1] + v[(row + 2)*N + col + 2]) == 10) friends++;
        }

        // Manual handling for the last two columns. Only vertical and backward diagonal.
        // Vertical.
        if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
        // Backward diagonal.
        if ((v[row*N + col] + v[(row + 1)*N + col - 1] + v[(row + 2)*N + col - 2]) == 10) friends++;
        col++;    // Advancing to the last column.

        // Vertical.
        if ((v[row*N + col] + v[(row + 1)*N + col] + v[(row + 2)*N + col]) == 10) friends++;
        // Backward diagonal.
        if ((v[row*N + col] + v[(row + 1)*N + col - 1] + v[(row + 2)*N + col - 2]) == 10) friends++;
    }

    if (!extend_rows){
        /* Manual handling for the last two rows if they are the final two
         * rows of the full 2D array. Only horizontal.
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
