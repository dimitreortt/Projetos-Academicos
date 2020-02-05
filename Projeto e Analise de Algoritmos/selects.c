#include "trabalho.h"

int Partition(int *A, int p, int r){
	int j;
	int x = A[r];
	int i = p - 1;
	for(j = p; j < r; j++){
		if (A[j] <= x){
 			i = i + 1; 
 			troca(&A[i], &A[j]);
 		}
 	}
	troca(&A[i + 1], &A[r]);
	return i + 1;
}

int RandomizedPartition(int * A, int p, int r){
	int i = p;
	if(p < r){
		i = p + (rand()%(r-p));
		troca(&A[i], &A[r]);
		return Partition(A, p, r);
	}
	return i;
}

int RandomizedSelect(int * A, int p, int r, int k){
	int i, q;

	if(p == r){
		return A[p];
	}
	q = RandomizedPartition(A, p, r);
	i = q;
	if(k == i){
		return A[q];
	}
	else if(k < i){
		return RandomizedSelect(A, p, q - 1, k);
	}
	else{
		return RandomizedSelect(A, q + 1, r, k);
	}
}