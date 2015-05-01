#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char** argv){
	int rank,size,epp;
	int* A1=NULL;
	int* A2=NULL;
	int* Rec1=NULL;
	int* Rec2=NULL;
	int i,n;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
			printf("Enter size of arrays...\n");
			scanf("%d",&n);
			epp=n/size+(n%size==0?0:1);
			A1=(int*)malloc(sizeof(int)*size*epp);
			A2=(int*)malloc(sizeof(int)*size*epp);
			for(i=0;i<n;i++){
				printf("Enter A1[%d]:",i);
				scanf("%d",&A1[i]);
				printf("Enter A2[%d]:",i);
				scanf("%d",&A2[i]);
			}
			for(i=n;i<size*epp;i++){
				A1[i]=0;
				A2[i]=0;
			}
	}
	MPI_Bcast(&epp,1,MPI_INT,0,MPI_COMM_WORLD);
	Rec1=(int*)malloc(sizeof(int)*epp);
	Rec2=(int*)malloc(sizeof(int)*epp);
	MPI_Scatter(A1,epp,MPI_INT,Rec1,epp,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A2,epp,MPI_INT,Rec2,epp,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<epp;i++)
		Rec1[i]*=Rec2[i];
	MPI_Gather(Rec1,epp,MPI_INT,A1,epp,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("Data gathered : ");
		for(i=0;i<n;i++)
			printf("%d ",A1[i]);
		printf("\n");
	}
	MPI_Finalize();
}

