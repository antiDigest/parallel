#include<omp.h>
#include<stdio.h>
int main(){
	#pragma omp parallel
	{
		int ID=omp_get_thread_num();
		printf("Hello by %d\n",ID);
		printf("World by %d\n",ID);
	}
	return 0;
}
