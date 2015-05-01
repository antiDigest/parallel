#include<omp.h>
#include<stdio.h>

int fibonacci(int x){
	int f[2],i;			
	if(x==1){
		return 0;	
	}
	else if(x==2){
		return 1;
	}
	else {
		#pragma omp parallel for
		for(i=1;i<=2;i++){
			f[i-1]=fibonacci(x-i);		
			printf("Thread %d calculates term %d\n",omp_get_thread_num(),x-i);		
		}
		return f[0]+f[1];		
	}
}

int main(){
	int x;
	omp_set_num_threads(2);
	omp_set_nested(1);
	printf("Enter which term to be found out : ");
	scanf("%d",&x);
  	printf("%dth term is : %d\n",x,fibonacci(x));
	return 0;
}
