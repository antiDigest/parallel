#include<mpi.h>
#include<stdio.h>

int main(int argc,char** argv){
	int LIMIT=4;
	int rank,size,ctr=0;
	int data=2;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	while(ctr<LIMIT){
		if(rank==0){
			MPI_Send(&data,1,MPI_INT,1,0,MPI_COMM_WORLD);
			printf("Master Sends %d\n",data);
			MPI_Recv(&data,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Master Recieves %d\n",data);
		}
		else{
			MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Slave Recieves %d\n",data);
			data*=2;
			MPI_Send(&data,1,MPI_INT,0,0,MPI_COMM_WORLD);
			printf("Slave Sends %d\n",data);
		}
		ctr++;
	}
	MPI_Finalize();
}
