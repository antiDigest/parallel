#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI		3.14159265358979323846
#include <mpi.h>

/* main program */

int main(int argc, char* argv[]) {

    char* usage_fmt = "usage:  %s number_of_samples seed\n";
    char* end_ptr_for_strtol;

    /* initialize for MPI */
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        fprintf(stderr, "MPI initialization error\n");
        return EXIT_FAILURE;
    }
    int nprocs, myID;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myID);

    /* process command-line arguments */
    if (argc != 3)  {
        fprintf(stderr, usage_fmt, argv[0]);
        MPI_Finalize(); exit(EXIT_FAILURE);
    }
    long num_samples = strtol(argv[1], &end_ptr_for_strtol, 10);
    if (*end_ptr_for_strtol != '\0') {
        fprintf(stderr, usage_fmt, argv[0]);
        exit(EXIT_FAILURE);
    }
    long seed = strtol(argv[2], &end_ptr_for_strtol, 10);
    if (*end_ptr_for_strtol != '\0') {
        fprintf(stderr, usage_fmt, argv[0]);
        exit(EXIT_FAILURE);
    }

    /* do calculation */ 
    srand((unsigned int) seed);
    int count = 0;
    int local_count = 0;
    int i;
    double x, y;
    double pi = 0;
    for (i = myID; i < num_samples; i += nprocs) {
        x = (double) rand() / (double) (RAND_MAX);
        y = (double) rand() / (double) (RAND_MAX);
        if ((x*x + y*y) <= 1.0)
            ++local_count;
    }
    MPI_Reduce(&local_count, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myID == 0)
        pi = 4.0 * (double) count / (double) num_samples;

    if (myID == 0) {
        printf("MPI program results with %d processes:\n", nprocs);
        printf("number of samples = %ld, seed = %ld\n", num_samples, seed);
        printf("estimated pi = %12.10f\n", pi);
        printf("difference between estimated pi and math.h M_PI = %12.10f\n", 
                fabs(pi - M_PI));
    }

    /* clean up and return */
    MPI_Finalize();
    return EXIT_SUCCESS;
}
