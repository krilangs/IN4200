#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../read_graph_from_file1/read_graph1_main.c"
#include "../read_graph_from_file2/read_graph2_main.c"
#include "../count_mutual_links1/count_links1_main.c"
#include "../count_mutual_links2/count_links2_main.c"
#include "../top_n_webpages/top_webpages.c"

void test_2Dtable(){
    printf("\n---------------------------------");
    printf("\nExpect the following:\n");
    printf("Nodes: 8    Edges: 17\n");

    int M[8][8] = {{0, 0, 0, 0, 0, 0, 1, 0},
                   {1, 0, 1, 1, 0, 0, 0, 0},
                   {1, 0, 0, 0, 0, 0, 0, 0},
                   {0, 1, 0, 0, 0, 0, 0, 0},
                   {0, 0, 1, 1, 0, 0, 1, 0},
                   {0, 0, 0, 1, 1, 0, 0, 1},
                   {0, 0, 0, 0, 1, 0, 0, 1},
                   {0, 0, 0, 0, 1, 1, 1, 0},};

    printf("2D table:\n");
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            printf(" %d ", M[i][j]);
        }
        printf("\n");
    }
}

void test_mutual_linkages(){
    printf("CRS:\n");
    printf("row_ptr= 0| 1| 4| 5| 6| 9| 12| 14| 17|\n");
    printf("col_idx= 6 |0 |2 |3 |0 |1 |2 |3 |6 |3 |4 |7 |4 |7 |4 |5 |6 |\n");
    printf("\nMutual web linkages: 13\n");
    printf("0: 2| 1: 0| 2: 4| 3: 6| 4: 5| 5: 2| 6: 4| 7: 3|\n");
}

void test_top_webpages(){
    printf("Webpage no. 3 -> 6 linkages.\n"\
           "Webpage no. 4 -> 5 linkages.\n"\
           "Webpage no. 2 -> 4 linkages.\n"\
           "Webpage no. 6 -> 4 linkages.\n"\
           "Webpage no. 7 -> 3 linkages.\n"\
           "Webpage no. 0 -> 2 linkages.\n"\
           "Webpage no. 5 -> 2 linkages.\n"\
           "Webpage no. 1 -> 0 linkages.\n");
}

int main()
{
    /* Test that our functions give the right answers by comparing
     * our calculated values with known values from the project
     * example in a text file "8-webpages.txt".
     * First we calculate our value with the implemented functions,
     * then compare to the expected values from the project example.
    */
    int N;
    char** test_table;
    char* file = "../8-webpages.txt";
    printf("File: %s\n", file);
    printf("*Test 2D table format:\n");
    read_graph_from_file1(file, &N, &test_table);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf(" %d ", test_table[i][j]);
        }
        printf("\n");
    }

    int *num_involvements1 = (int*)calloc(N, sizeof (int));
    int mutual_linkages1 = count_mutual_links1(N, test_table, num_involvements1);
    printf("Mutual web linkages: %i\n", mutual_linkages1);
    printf("Number of involvements per webpage as outbound (webpage: no.involvements|):\n");
    for (int i = 0; i < N; i++){
        printf("%i: %i| ", i, num_involvements1[i]);
    }
    printf("\n");

    free(test_table);
    free(num_involvements1);

    int N_links;
    int *row_ptr, *col_idx;
    int n = N;
    printf("\n*Test CRS format:\n");
    read_graph_from_file2(file, &N, &N_links, &row_ptr, &col_idx);
    printf("col_idx= ");
    for (int i=0; i<N_links;i++)
        printf("%d |", col_idx[i]);

    printf("\nrow_ptr= ");
    for (int j=0; j<N+1; j++)
        printf("%d| ", row_ptr[j]);

    int *num_involvements2 = (int*)calloc(N, sizeof (int));
    int mutual_linkages = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements2);
    printf("\nMutual web linkages: %i\n", mutual_linkages);
    printf("Number of involvements per webpage as outbound:\n");
    for (int i = 0; i < N; i++){
        printf("%i: %i| ", i, num_involvements2[i]);
    }
    printf("\n");
    top_n_webpages(N, num_involvements2, n);

    free(row_ptr);
    free(col_idx);
    free(num_involvements2);

    test_2Dtable();
    test_mutual_linkages();
    test_top_webpages();
    return 0;
}


