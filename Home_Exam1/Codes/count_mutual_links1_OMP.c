#include <stdio.h>
#include <omp.h>

int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
    /* Count the total number of mutual webpage linkage occurrences
           with the 2D table format, as well as the number of involvements
           per webpages outbound for such mutual linkage occurrences.
           Input:
           * N               : Number of webpages.
           * table2D         : 2D NxN-matrix containing the web graph data.
           * num_involvements: Allocated array of length N containing the
                               number of involvements per webpage.
        */
    int mutual_linkages = 0;
    int num_threads;
    int threads = 5;

    #pragma omp parallel for reduction(+:mutual_linkages, num_involvements[:N]) schedule(auto) num_threads(threads)
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if (table2D[j][i] == 1){
                for (int k=0; k<N; k++){
                    num_involvements[i] += table2D[j][k];
                }
                num_involvements[i] --;
            }
        }
        mutual_linkages += num_involvements[i];
        num_threads = omp_get_num_threads();
    }
    // Account for double counting of linkages
    mutual_linkages /= 2;

    printf("Number of threads: %d\n", num_threads);

    return mutual_linkages;
}
