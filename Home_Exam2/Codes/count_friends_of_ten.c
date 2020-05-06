int count_friends_of_ten(int M, int N, int** v)
{
    /* Count the total number of "triple-friends of 10"
       inside a 2D array of dimension MxN.
       Input:
       * M : Number of rows.
       * N : Number of columns.
       * v : 2D array of dimension MxN.
    */
    int tot_friends = 0;

    // Check horizontal.
    for (int i = 0; i < M; i++){
        for (int j = 2; j < N; j++){
            if (v[i][j] + v[i][j-1] + v[i][j-2] == 10){
                tot_friends ++;
            }
        }
    }

    for (int i = 0; i < M-2; i++){
        // Check vertical.
        for (int j = 0; j < N; j++){
            if (v[i][j] + v[i+1][j] + v[i+2][j] == 10){
                tot_friends ++;
            }
        }
        // Check backward diagonal.
        for (int j = 2; j < N; j++){
            if (v[i][j] + v[i+1][j-1] + v[i+2][j-2] == 10){
                tot_friends ++;
            }
        }
        // Check forward diagonal.
        for (int j = 0; j < N-2; j++){
            if (v[i][j] + v[i+1][j+1] + v[i+2][j+2] == 10){
                tot_friends ++;
            }
        }
    }

    return tot_friends;
}
