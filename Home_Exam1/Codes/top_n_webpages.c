void top_n_webpages(int num_webpages, int *num_involvements, int n)
{
    /* Find the top n web pages with respect to the number of
       involvements in mutual linkages.
       Input:
       * num_webpages    : Number of web pages.
       * num_involvements: Allocated array of length N containing
                           the number of involvements per web page.
       * n               : Number of the top involved web pages
                           we choose to look at.
    */
    if (n > num_webpages){
        printf("\nNumber of top web pages wanted is bigger than total number of web pages.\n");
        n = num_webpages;
    }

    int *val_list = (int*)malloc(n*sizeof(int));   // Array storing number of linkages for top web pages
    int *idx_list = (int*)malloc(n*sizeof(int));   // Array store top web pages

    // Loop through the array n times, to find the maximum value of each iteration.
    for (int i = 0; i < n; i++){
        int maxval = -1;
        int maxidx = -1;
        for (int j = 0; j < num_webpages; j++){
            if (num_involvements[j] > maxval){
                maxval = num_involvements[j];
                maxidx = j;
            }
        }
        val_list[i] = maxval;
        idx_list[i] = maxidx;
        /* "Remove" this maximum value from num_involvements array,
         * since we want to find the next highest value next iteration.
         */
        num_involvements[maxidx] = -1;
    }

    for (int i = 0; i < n; i++){
        printf("Web page no. %d -> %d linkages.\n", idx_list[i], val_list[i]);
    }

    free(val_list);
    free(idx_list);
}
