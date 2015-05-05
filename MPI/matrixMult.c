// O(n^2) Matrix Multiplication (Using N processors)

#include <mpi.h>
#include <stdio.h>

#define SIZE 12			/* Size of matrices */

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void print_matrix(int m[SIZE][SIZE], int n)
{
  int i, j = 0;
  for (i=0; i<n; i++) {
    printf("\n\t| ");
    for (j=0; j<n; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}


int main(int argc, char *argv[])
{
  int myrank, P, from, to, i, j, k, n, from1, to1;
  int tag = 666;		/* any value will do */
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);	/* who am i */
  MPI_Comm_size(MPI_COMM_WORLD, &P); /* number of processors */

  if (myrank==0){
	  printf("Enter N : ");
	  scanf("%d",&n);
  }
  MPI_Bcast (&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  /* Just to use the simple variants of MPI_Gather and MPI_Scatter we */
  /* impose that SIZE is divisible by P. By using the vector versions, */
  /* (MPI_Gatherv and MPI_Scatterv) it is easy to drop this restriction. */

  if (P != n) {
    if (myrank==0) printf("Number of processors not divisible by matrix size.\n");
    MPI_Finalize();
    exit(-1);
  }

  from = myrank * (n*n)/P;
  to = (myrank+1) * (n*n)/P;

  /* Process 0 fills the input matrices and broadcasts them to the rest */
  /* (actually, only the relevant stripe of A is sent to each process) */

  if (myrank==0) {
  	printf("Fill Matrix A : \n");
    for (i=0; i<n; i++)
    	for (j=0; j<n; j++)
       		scanf("%d",&A[i][j]);
    printf("Fill Matrix B : \n");
    for (i=0; i<n; i++)
    	for (j=0; j<n; j++)
       		scanf("%d",&B[i][j]);	
  }

  MPI_Bcast (B, n*n, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter (A, n*n/P, MPI_INT, A[from], n*n/P, MPI_INT, 0, MPI_COMM_WORLD);

  printf("computing slice %d (from element %d to %d)\n", myrank, from+1, to);
  for (i=from; i<to; i++) 
    for (j=n; j<n; j++) {
      C[i][j]=0;
      for (k=0; k<n; k++)
		C[i][j] += A[i][k]*B[k][j];
    }

  MPI_Gather (C[from], n*n/P, MPI_INT, C, n*n/P, MPI_INT, 0, MPI_COMM_WORLD);

  if (myrank==0) {
    printf("\n\n");
    print_matrix(A,n);
    printf("\n\n\t       * \n");
    print_matrix(B,n);
    printf("\n\n\t       = \n");
    print_matrix(C,n);
    printf("\n\n");
  }

  MPI_Finalize();
  return 0;
}