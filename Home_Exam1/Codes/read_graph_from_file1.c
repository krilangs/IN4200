char** matrix2D(int N)
{
    // Initialize a 2D NxN-matrix with zeros.
    char *M_temp = (char*)calloc(N*N, sizeof(char));
    char **M = (char**)calloc(N, sizeof(char*));
    for (int i=0; i<N; i++) {
        M[i] = &(M_temp[i*N]);
    }
    return M;
}

void read_graph_from_file1(char *filename, int *N, char ***table2D)
{
    /* Read file, allocate a 2D table and extract the data into the table.
       Input:
       * filename: Name of the web graph.
       * N       : Number of web pages.
       * table2D : 2D NxN-matrix containing the web graph data.
    */
    int nodes, links, N_links;

    // First read in the data
    FILE *infile;
    infile = fopen(filename, "r");

    // Skip the unwanted lines in the file and store the number of nodes and edges
    fscanf(infile, "%*[^\n]\n");
    fscanf(infile, "%*[^\n]\n");
    fscanf(infile, "%*s%*s%d%*s%d \n", N, &N_links);
    fscanf(infile, "%*[^\n]\n");
    printf("N=%d, N_links=%d\n", *N, N_links);

    *table2D = matrix2D(*N+1);  // Allocate a 2D matrix with zeros of dimension NxN

    // Check that the table is allocated correctly
    if ((*table2D) == NULL)
      {
        printf("Error in allocating memory.\n");
      }

    // Read web graph into the table
    while (fscanf(infile, "%i %i \n", &nodes, &links) != EOF){
        if (nodes != links){
            (*table2D)[links][nodes] = 1;
        }
    }

    fclose(infile);
}
