#include<omp.h>
#include<stdio.h>

int main(){
	int i=0;
	omp_set_num_threads(5);
	printf("SINGLE\n");
	#pragma omp parallel
	{
		printf("Executed by %d \n",omp_get_thread_num());
		#pragma omp single
		{
				printf("Executed ONLY by %d \n",omp_get_thread_num());
		}
	}
	printf("\nMASTER\n");
	#pragma omp parallel
	{
		printf("Executed by %d \n",omp_get_thread_num());
		#pragma omp master
		{
				printf("Executed ONLY by %d \n",omp_get_thread_num());
		}
	}
	return 0;
}
