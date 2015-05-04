#include <stdio.h>
#include <mpi.h>
// int x[200];
int main(int argc,char *argv[])
{
int my_id,numprocess,n,sum=0,tmp,i;
int x[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
MPI_Comm_size(MPI_COMM_WORLD, &numprocess);
// printf("%d %d\n",my_id,numprocess );
if(my_id==0)
{
printf("Enter value of n :");
scanf("%d",&n);
// for(i=0;i<numprocess;i++) //USING SIMPLE MPI_SEND
// {
// MPI_Send(&n,1,MPI_INT,i,i,MPI_COMM_WORLD);
// }
MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); //USING MPI_BCAST. NO NEED TO GIVE DESTINATION ID.
for(i=my_id;i<n;i=i+numprocess)
{
sum=sum+x[i];
}
// for(i=1;i<numprocess;i++)
// {
// MPI_Recv(&tmp,1,MPI_INT,i,i,MPI_COMM_WORLD,&status);
// sum=sum+tmp;
// }
}
else
{
// MPI_Recv(&n,1,MPI_INT,0,my_id,MPI_COMM_WORLD,&status);
MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
for(i=my_id;i<n;i=i+numprocess)
{
sum=sum+x[i];
}
// MPI_Send(&sum,1,MPI_INT,0,my_id,MPI_COMM_WORLD);
}
MPI_Reduce(&sum,&tmp,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
if ( my_id == 0 )
{
printf("Total Sum is:%d\n",tmp);
}
MPI_Finalize();
return 0;
}
