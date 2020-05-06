#include "common.h"
#include "count_friends_of_ten.c"

int main(int argc, char **argv)
{
    /* Serial program that allocates a 2D array of dimension MxN,
       assigns it with appropriate random integer values,
       then calls a function for counting
       triple-friends of 10 in the 2D array. Also time the
       counting function.
    */
    // Test the counting function with a known solution from home exam.
    int** v;
    int M, N;

    generate_known_2d_array(&v);
    int tot_friends_test = count_friends_of_ten(4, 5, v);

    printf("Test counting for known solution:\n");
    printf(" 2D array dimension: 4x5\n");
    printf(" Total number of friends of 10 (should be 7): %i\n", tot_friends_test);

    // Count total number of triple-friends of 10 for a randomly generated 2D array.
    N = atoi(argv[1]);  // Columns.
    M = atoi(argv[2]);  // Rows.

    clock_t start_generate = clock();
    generate_random_2d_array(M, N, &v);
    clock_t stop_generate = clock();
    double time_generate = (double) (stop_generate - start_generate)*1.0/CLOCKS_PER_SEC;

    clock_t start_count = clock();
    int tot_friends = count_friends_of_ten(M, N, v);
    clock_t stop_count = clock();
    double time_count = (double) (stop_count - start_count)*1.0/CLOCKS_PER_SEC;

    printf("Serial counting:\n");
    printf(" 2D array dimension: %ix%i\n", M, N);
    printf(" Total number of friends of 10: %i\n", tot_friends);
    printf(" 2D array generated in: %f s\n", time_generate);
    printf(" Time calculating friends of 10: %f s\n", time_count);

    // Deallocate 2D array v.
    free(v[0]);
    free(v);

    return 0;
}
