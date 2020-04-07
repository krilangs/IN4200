#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#include "read_graph_from_file1.c"
#include "read_graph_from_file2.c"
#include "count_mutual_links1_OMP.c"
#include "count_mutual_links2_OMP.c"
#include "top_n_webpages_OMP.c"

int main(int argc, char *argv[])
{
    /* Terminal>... Test_functions_OMP.c <filename> <Task> <n>
     * - <filename> = name of the text file to be read.
     * - <Task> = 2D to run functions for 2D table, which runs:
     *   -> read_graph_from_file1()
     *   -> OMP_count_mutual_links1()
     * - <Task> = CRS to run functions for CRS format, which runs:
     *   -> read_graph_from_file2()
     *   -> OMP_count_mutual_links2()
     *   -> OMP_top_n_webpages()
     * - <n> = number of top web pages to look at (for CRS)
     */
    if (!strcmp(argv[2], "2D")){
        printf("Run 2D table format parallelized:\n");
        int N;
        char** test_table;
        char* file = argv[1];   // Choose text file to read
        printf("File: %s\n", file);

        // Read file and time the reading
        double start_read = omp_get_wtime();
        read_graph_from_file1(file, &N, &test_table);
        double stop_read = omp_get_wtime();
        double time_read = (double) (stop_read - start_read)*1000;

        int *num_involvements = (int*)calloc(N, sizeof (int));

        // Count mutual linkages and take time counting
        double start_count = omp_get_wtime();
        int mutual_linkages1 = count_mutual_links1(N, test_table, num_involvements);
        double stop_count = omp_get_wtime();
        double time_count = (double) (stop_count - start_count)*1000;

        printf("\nMutual web linkages: %i\n", mutual_linkages1);
        printf("Number of involvements per web page as outbound (web page: no.involvements|):\n");

        if (N > 100){
            for (int i = 0; i < 100; i++){
                printf("%i: %i| ", i, num_involvements[i]);
            }
        }
        else{
            for (int i = 0; i < N; i++){
                printf("%i: %i| ", i, num_involvements[i]);
            }
        }
        printf("\n");

        printf("\nTime taken reading: %f ms \n", time_read);
        printf("Time taken counting: %f ms \n", time_count);

        free(test_table);
        free(num_involvements);
    }
    else if (!strcmp(argv[2], "CRS")){
        printf("Run CRS format parallelized:\n");

        int num_webpages, N_links;
        int *row_ptr, *col_idx;
        char* file = argv[1];   // Choose text file to read
        int n = atoi(argv[3]);  // Choose how many of the num_webpages to look at
        printf("File: %s\n", file);

        // Read file and time the reading
        double start_read = omp_get_wtime();
        read_graph_from_file2(file, &num_webpages, &N_links, &row_ptr, &col_idx);
        double stop_read = omp_get_wtime();
        double time_read = (double) (stop_read - start_read)*1000;

        int *num_involvements = (int*)calloc(num_webpages, sizeof (int));

        // Count mutual linkages and take time counting
        double start_count = omp_get_wtime();
        int mutual_linkages = count_mutual_links2(num_webpages, N_links, row_ptr, col_idx, num_involvements);
        double stop_count = omp_get_wtime();
        double time_count = (double) (stop_count - start_count)*1000;

        printf("\nMutual web linkages: %i\n", mutual_linkages);
        printf("Number of involvements per web page as outbound (web page: no.involvements|):\n");

        if (num_webpages > 100){
            for (int i = 0; i < 100; i++){
                printf("%i: %i| ", i, num_involvements[i]);
            }
        }
        else{
            for (int i = 0; i < num_webpages; i++){
                printf("%i: %i| ", i, num_involvements[i]);
            }
        }
        printf("\n");
        printf("\nTop %i web pages: \n", n);

        // Find/sort top web pages and measure the time
        double start_top = omp_get_wtime();
        top_n_webpages(num_webpages, num_involvements, n);
        double stop_top = omp_get_wtime();
        double time_top = (double) (stop_top - start_top)*1000;

        printf("\nTime taken reading: %f ms \n", time_read);
        printf("Time taken counting: %f ms \n", time_count);
        printf("Time taken sorting top web pages: %f ms \n", time_top);

        free(row_ptr);
        free(col_idx);
        free(num_involvements);
    }
    else {
        printf("Choose either 2D or CRS in terminal.");
    }
    return 0;
}
