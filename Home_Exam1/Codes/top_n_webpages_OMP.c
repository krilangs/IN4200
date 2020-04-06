#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void top_n_webpages(int num_webpages, int *num_involvements, int n)
{
    /* Find the top n webpages with respect to the number of
       involvements in mutual linkages.
       Input:
       * num_webpages    : Number of webpages.
       * num_involvements: Allocated array of length N containing
                           the number of involvements per webpage.
       * n               : Number of the top involved webpages we
                           we choose to look at.
    */
    if (n > num_webpages){
        printf("\nNumber of top webpages wanted is bigger than total number of webpages.\n");
        n = num_webpages;
    }

    int threads = omp_get_max_threads();	// number of nodes to parallelize.
    threads = 4;
    int frac = num_webpages/threads;		// the fraction of the array each node will analyze.
    int remainder = num_webpages % threads;	// the remaining values which must also be accounted for.

    /* Have each node pick out a top_n_webpages list, and
       compare them all using a single node to summarize.
    */
    int *val_list = (int*) malloc(threads * n * sizeof(int));
    int *idx_list = (int*) malloc(threads * n * sizeof(int));

    /* Node no. 1 finds the top n webpages of values [0, num_webpages/threads>.
     * Node no. 2 finds the top n webpages of values [(num_webpages/threads), 2*num_webpages/threads>
     * Node no. 3 finds the top n webpages of values [(2*num_webpages/threads), 3*num_webpages/threads>
     * Node no. 4 finds the top n webpages of values [(3*num_webpages/threads), 4*num_webpages/threads]
    */

    int maxval, maxidx, mythread;
    // Loop through the array n times, to find the maximum value of each iteration.
    #pragma omp parallel num_threads(threads)
    {
        mythread = omp_get_thread_num();
        for (int i = 0; i < n; i++){
            maxval = -1;
            maxidx = -1;
            for (int j = mythread*frac; j < (mythread + 1)*frac; j++){
                if (num_involvements[j] > maxval){
                    maxval = num_involvements[j];
                    maxidx = j;
                }
            }
            val_list[i + mythread*n] = maxval;
            idx_list[i + mythread*n] = maxidx;

            /* Need to remove this value from the num_involvements array so
               it doesn't get reconglized on subsequent iterations. Could avoid
               damaging the array using memcpy, but don't seem to need it later. */
            num_involvements[maxidx] = num_involvements[maxidx] * (-1);
        }
    }

    // Go through each node's top n findings, as well as the remainders
    int dmyidx = 0;
    int restsbool = 0;
    int *winner_val_list = (int*)malloc(n*sizeof(int));
    int *winner_idx_list = (int*)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++){
        restsbool = 0; maxval = -1; maxidx = -1;
        for (int j = 0; j < (threads * n); j++){
            if (val_list[j] > maxval){
                maxval = val_list[j];
                maxidx = idx_list[j];
                dmyidx = j;
            }
        }

        // Go through the remaining values of the num_involvements array as well
        for (int k = (threads*frac); k < num_webpages; k++){
            if (num_involvements[k] > maxval){
                maxval = num_involvements[k];
                maxidx = k;
                restsbool = 1;
            }
        }

        winner_val_list[i] = maxval;
        winner_idx_list[i] = maxidx;

        // Need to check where the current max value occurred, and remove it for the next iteration.
        if (restsbool){
            num_involvements[maxidx] = -1;
        }
        else {
            val_list[dmyidx] = -1;
        }
    }

    for (int i = 0; i < n; i++){
        printf("Webpage no. %d -> %d linkages.\n",\
               winner_idx_list[i], winner_val_list[i]);
    }

    // Finalize.
    free(val_list);
    free(idx_list);
    free(winner_val_list);
    free(winner_idx_list);
}