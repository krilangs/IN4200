int count_mutual_links1(int N, char **table2D, int *num_involvements)
{
    /* Count the total number of mutual web page linkage occurrences
       with the 2D table format, as well as the number of involvements
       per web page as outbound for such mutual linkage occurrences.
       Input:
       * N               : Number of web pages.
       * table2D         : 2D NxN-matrix containing the web graph data.
       * num_involvements: Allocated array of length N containing the
                           number of involvements per web page.
    */
    int mutual_linkages = 0;

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
    }
    // Account for double counting of linkages
    mutual_linkages /= 2;

    return mutual_linkages;
}
