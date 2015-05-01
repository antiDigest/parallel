#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
	int n=1024;
	int i=0;
	float x;
	omp_set_num_threads(10);
	float* pi=(float*)malloc(sizeof(float)*n); 
	float PI=0.0f;
	#pragma omp parallel for
	for(i=0;i<n;i++){	
		x=(i+0.5)/n;
		//printf("Thread %d is working\n",omp_get_thread_num());
		//printf("PI is %f,adding %f\n",pi,x);
		pi[i]=((4/(1+x*x))/n);
	}
	#pragma omp parallel for reduction(+:PI)
	for(i=0;i<n;i++){
		PI+=pi[i];
	}
	printf("PI : %f\n",PI);
	return 0;
}

