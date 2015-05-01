#include<stdio.h>
#include<omp.h>
int tree[512];

void  createTree(int i){
	int ch;
	printf("Enter node %d Data :",i);
	scanf("%d",&tree[i]);
	printf("Is there a Left node of NODE %d ? [0 if not]: ",i);
	scanf("%d",&ch);
	if(ch!=0)
		createTree(2*i);
	printf("Is there a Right node of NODE %d ? [0 if not]: ",i);
	scanf("%d",&ch);
	if(ch!=0)
		createTree(2*i+1);
}

void searchTree(int data,int i){
	int k;
	if(tree[i]!=0&&found==0){
	if(tree[i]==data){
		printf("Node at %d \n",i);
	}
	else{
		omp_set_num_threads(2);
		#pragma omp parallel for
		for(k=0;k<2;k++){
			searchTree(data,2*i+k);
		}
	}
	}
}	
	
int main(){
	int d;
	printf("Creating tree \n");
	createTree(1);
	omp_set_num_threads(2);
	printf("Enter data to be searched : ");
	scanf("%d",&d);
	searchTree(d,1);
}
