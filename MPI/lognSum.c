#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char** argv){
	int rank,size;
	int i,n;
	int* A=NULL;
	
	int D[2],sum;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int ctr=size*2;
	A=(int*)malloc(sizeof(int)*size*2);
	if(rank==0){
			printf("Enter %d Elements :\n",size*2);
			for(i=0;i<size*2;i++)
				scanf("%d",&A[i]);
	}
	while(ctr!=1){		
		MPI_Scatter(A,2,MPI_INT,D,2,MPI_INT,0,MPI_COMM_WORLD);
		sum=D[0]+D[1];
		MPI_Gather(&sum,1,MPI_INT,A,1,MPI_INT,0,MPI_COMM_WORLD);
		ctr/=2;
	}
	if(rank==0)
		printf("Total Sum : %d\n",A[0]);
	MPI_Finalize();
}

