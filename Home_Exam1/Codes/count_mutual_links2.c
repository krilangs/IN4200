int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements)
{   /* Count the total number of mutual web page linkage occurrences with the CRS format,
       as well as the number of involvements per web pages outbound for such mutual linkage
       occurrences.
       Input:
       * N               : Number of web pages.
       * N_links         : Number of direct links between the web pages.
       * row_ptr         : 1D array of length N+1, contains indices at which new rows start
                           where there are links.
       * col_dix         : 1D array of length Nlinks, with column indices of all the direct links.
       * num_involvements: Allocated array of length N containing the
                           number of involvements per web page.
    */
    int mutual_linkages = 0;
    int count;

    for (int i = 0; i < N; i++) {
        if ((row_ptr[i+1]-row_ptr[i])>1){
            for (int j = row_ptr[i]; j <row_ptr[i+1]; j++) {
                count = row_ptr[i+1] - row_ptr[i] - 1;
                num_involvements[col_idx[j]] += count;
                mutual_linkages += count;
            }
        }
    }
    // Account for double counting of linkages
    mutual_linkages /= 2;

    return mutual_linkages;
}
