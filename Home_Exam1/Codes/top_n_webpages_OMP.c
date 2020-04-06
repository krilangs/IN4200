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

    int threads = 8;   // Number of threads to use
    int frac = num_webpages/threads;

    int *vals = (int*) malloc(threads * n * sizeof(int));
    int *idx = (int*) malloc(threads * n * sizeof(int));

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
            vals[i + mythread*n] = maxval;
            idx[i + mythread*n] = maxidx;

            /* Remove this maximum value from num_involvements array,
             * since we want to find the next highest value next iteration.
             */
            num_involvements[maxidx] = num_involvements[maxidx] * (-1);
        }
    }

    // Go through each node's top n findings, as well as the remainders
    int dmyidx = 0;
    int rest_bool = 0;
    int *val_list = (int*)malloc(n*sizeof(int));
    int *idx_list = (int*)malloc(n*sizeof(int));

    for (int i = 0; i < n; i++){
        rest_bool = 0; maxval = -1; maxidx = -1;
        for (int j = 0; j < (threads * n); j++){
            if (vals[j] > maxval){
                maxval = vals[j];
                maxidx = idx[j];
                dmyidx = j;
            }
        }

        // Go through the remaining values of the num_involvements array as well
        for (int k = (threads*frac); k < num_webpages; k++){
            if (num_involvements[k] > maxval){
                maxval = num_involvements[k];
                maxidx = k;
                rest_bool = 1;
            }
        }

        val_list[i] = maxval;
        idx_list[i] = maxidx;

        // Need to check where the current max value occurred, and remove it for the next iteration.
        if (rest_bool){
            num_involvements[maxidx] = -1;
        }
        else {
            vals[dmyidx] = -1;
        }
    }

    for (int i = 0; i < n; i++){
        printf("Webpage no. %d -> %d linkages.\n",\
               idx_list[i], val_list[i]);
    }

    // Finalize.
    free(vals);
    free(idx);
    free(val_list);
    free(idx_list);
}
