#include<omp.h>
#include<stdio.h>
int main(){
	int A[20],B[20][20],C[20];
	int n;
	int i,j,k;

	printf("Enter the value of N :");
	scanf("%d",&n);
	printf("Enter Array : \n");

	for(i=0;i<n;i++)
		scanf("%d",&A[i]);

	double starttime=omp_get_wtime();

	omp_set_num_threads(n*n);

	#pragma omp parallel for
	for(i=0;i<n;i++)
	{
		#pragma omp parallel for
		for(j=0;j<n;j++)
		{
			if(A[i]>A[j])
			{
				B[i][j]=1;
			}
			else
				B[i][j]=0;
		}
		int x=0;
		#pragma omp parallel for reduction(+:x)
 		for(j=0;j<n;j++)
 		{
			x+=B[i][j];
		}
		B[i][0]=x;
		C[B[i][0]]=A[i];
	}
	double endtime=omp_get_wtime()-starttime;

	printf("Sorted Array: ");
	for(i=0;i<n;i++)
		printf("%d ",C[i]);
	printf("\nTook %f seconds\n",endtime);
	return 0;
}

