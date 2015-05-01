#include<omp.h>
#include<stdio.h>

int main(){
	int i=0;
	omp_set_num_threads(5);
	#pragma omp parallel
	{
		printf("A(%d)\n",omp_get_thread_num());
		printf("B(%d)\n",omp_get_thread_num());
		printf("C(%d)\n",omp_get_thread_num());	
		#pragma omp critical
		{
			printf("This is Critcal (%d) ",omp_get_thread_num());
			printf("For (%d)",omp_get_thread_num());
			printf("the thread (%d) \n",omp_get_thread_num());
		}
		printf("D(%d)\n",omp_get_thread_num());
		printf("E(%d)\n",omp_get_thread_num());
	}
	return 0;
}
