#include<mpi.h>
#include<stdio.h>

int main(int argc,char** argv){
	int rank,size;
	int data;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
		data=9000;
	MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
		if(rank==0){
			printf("Master sends %d\n",data);
		}
		else{
			printf("Slave %d recieves %d\n",rank,data);
		}
	MPI_Finalize();
}
