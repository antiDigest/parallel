#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char** argv){
	int rank,size,epp;
	int* dataSend=NULL;
	int i,n;
	float res;
	float pie;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
			printf("Enter the value of n\n");
			scanf("%d",&n);
	}

	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	res=0;

	for(i=0;i<n/size;i++)
	{
		res+=(4/(1+(((n/size)*rank+0.5+i)/n)*(((n/size)*rank+0.5+i)/n)))/n;
	}

	MPI_Reduce(&res,&pie,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		printf("The average is : %f\n",pie);
	}

	MPI_Finalize();
}

