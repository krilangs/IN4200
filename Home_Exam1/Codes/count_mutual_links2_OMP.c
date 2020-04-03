#include <stdio.h>
#include <omp.h>

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{   /* Count the total number of mutual webpage linkage occurrences with the CRS format,
       as well as the number of involvements per webpages outbound for such mutual linkage
       occurrences.
       Input:
       * N               : Number of webpages.
       * N_links         : Number of direct links between the webpages.
       * row_ptr         : 1D array of length N+1, contains indices at which new rows start
                           where there are links.
       * col_dix         : 1D array of length Nlinks, with column indices of all the direct links.
       * num_involvements: Allocated array of length N containing the
                           number of involvements per webpage.
    */
    int mutual_linkages = 0;
    int count;
    int num_threads;
    int threads = 6;

    #pragma omp parallel for reduction(+:mutual_linkages) private(count) schedule(auto) num_threads(threads)
    for (int i = 0; i < N; i++) {
        if ((row_ptr[i+1]-row_ptr[i])>1){
            for (int j = row_ptr[i]; j <row_ptr[i+1]; j++) {
                count = row_ptr[i+1] - row_ptr[i] - 1;
                num_involvements[col_idx[j]] += count;
                mutual_linkages += count;
            }
        }
        num_threads = omp_get_num_threads();
    }
    // Account for double counting of linkages
    mutual_linkages /= 2;

    printf("Number of threads: %d\n", num_threads);

    return mutual_linkages;
}
