#include<omp.h>
#include<stdio.h>
int main(){
	int A[10][10],B[10][10],C[10][10];
	int n,i,j,k;
	printf("Enter the value of N :");
	scanf("%d",&n);
	omp_set_num_threads(n*n*n);

	printf("Enter A:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&A[i][j]);
		}
	}

	printf("Enter B:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&B[i][j]);
		}
	}

	#pragma omp parallel for
	for(i=0;i<n;i++)
	{
		#pragma omp parallel for
		for(j=0;j<n;j++)
		{
			int x=0;
			#pragma omp parallel for reduction(+:x)
			for(k=0;k<n;k++)
			{
				x+=A[i][k]*B[k][j];
			}
			C[i][j]=x;
		}
	}

	printf("Matrix C:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}
	return 0;
}
