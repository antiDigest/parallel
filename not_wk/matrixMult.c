#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char** argv){
	int rank,size,epp;
	int* A=NULL;
	int* B=NULL;
	int* C=NULL;
	
	int i,j,n;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
			printf("Enter the value of N\n");
			scanf("%d",&n);	
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	A=(int*)malloc(sizeof(int)*n*n);
	B=(int*)malloc(sizeof(int)*n*n);
	if(rank==0){
			C=(int*)malloc(sizeof(int)*n*n);
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					printf("Enter A[%d][%d] : ",i,j);
					scanf("%d",&A[i*n+j]);
				}
			}
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					printf("Enter B[%d][%d] : ",i,j);
					scanf("%d",&B[i*n+j]);
				}
			}
	}
//	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(A,n*n,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(B,n*n,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==1){
		printf("Recieved A: \n");
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					printf("%d ",A[i*n+j]);
				}
				printf("\n");
			}
		printf("Recieved B: \n");
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					printf("%d ",B[i*n+j]);
				}
				printf("\n");
			}
	}
	int sum=0;
	for(i=0;i<n;i++)
		sum+=A[(rank/n)*n+i]*B[i*n+(rank%n)];
	
	MPI_Gather(&sum,1,MPI_INT,C,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
			printf("The matrix produced is :\n");
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					printf("%d ",C[i*n+j]);
				}
				printf("\n");
			}
	}
	MPI_Finalize();
}


