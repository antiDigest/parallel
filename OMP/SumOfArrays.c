#include<stdio.h>
#include<omp.h>
int main(){
	int i,n=5;
	int a[5]={1,2,3,4,5},b[5]={1,1,1,2,1},c[5];
	#pragma omp parallel for
	for(i=0;i<n;i++){
		c[i]=a[i]+b[i];
		printf("c[%d]=%d calculated by the thread %d\n",i,c[i],omp_get_thread_num());
	}
}
