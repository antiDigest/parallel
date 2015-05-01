#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char** argv){
	int rank,size,epp;
	int* dataSend=NULL;
	int i;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	epp=2;
	if(rank==0){
			printf("Master creating data...\n");
			dataSend=(int*)malloc(sizeof(int)*size*epp);
			for(i=0;i<epp*size;i++)
				dataSend[i]=i;
	}
	int* dataRecv1=(int*)malloc(sizeof(int)*epp);
	MPI_Scatter(dataSend,epp,MPI_INT,dataRecv1,epp,MPI_INT,0,MPI_COMM_WORLD);
	float subavg=0.0f;
	for(i=0;i<epp;i++)
		subavg+=dataRecv1[i];
	subavg/=epp;
	printf("%d calculates subavg as %f\n",rank,subavg);
	float finalAvg;
	MPI_Reduce(&subavg,&finalAvg,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("The average is : %f",finalAvg/size);
	}
	MPI_Finalize();
}

