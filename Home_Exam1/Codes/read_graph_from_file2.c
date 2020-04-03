#include <stdio.h>
#include <stdlib.h>
void read_graph_from_file2(char *filename, int *N, int *N_links, int **row_ptr, int **col_idx)
{   /* Read file and extract data with compressed row storage (CRS) format.
       Input:
       * filename: Name of the web graph.
       * N       : Number of web pages.
       * Nlinks  : Number of direct links between the web pages.
       * row_ptr : 1D array of length N+1, contains indices at which new rows start where
                   there are links.
       * col_dix : 1D array of length Nlinks, with column indices of all the direct links.
    */
    int fromnode, tonode;
    int pos = 0;

    // First read in the data
    FILE *infile;
    infile = fopen(filename, "r");

    // Skip the unwanted lines in the file and store the number of nodes and edges
    fscanf(infile, "%*[^\n]\n");
    fscanf(infile, "%*[^\n]\n");
    fscanf(infile, "%*s%*s%d%*s%d \n", N, N_links);
    fscanf(infile, "%*[^\n]\n");
    printf("N=%d, N_links=%d\n", *N, *N_links);

    *row_ptr = (int*)calloc((*N+1), sizeof(int));
    *col_idx = (int*)malloc((*N_links)*sizeof(int));
    (*row_ptr)[0] = 0;

    int *from_arr = (int*)calloc(*N_links, sizeof (int));
    int *to_arr = (int*)calloc(*N_links, sizeof (int));
    int *prev_row = (int*)calloc(*N, sizeof (int));

    while (fscanf(infile, "%i %i \n", &fromnode, &tonode) != EOF){
        if (fromnode != tonode){
            (*row_ptr)[tonode+1]++;
            from_arr[pos] = fromnode;
            to_arr[pos] = tonode;
            pos++;
        }
    }

    for (int i = 1; i < (*N); i++){
        (*row_ptr)[i+1] += (*row_ptr)[i];
    }
    for (int i = 0; i < pos; i++){
        (*col_idx)[(*row_ptr)[to_arr[i]] + prev_row[to_arr[i]]] = from_arr[i];
        prev_row[to_arr[i]]++;
    }

    free(from_arr);
    free(to_arr);
    free(prev_row);
    fclose(infile);
}
