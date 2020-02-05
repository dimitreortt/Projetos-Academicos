#include "trabalho.h"

int * le_A(int * A, int n){
	int i;

	srand((unsigned)time(NULL));

	for(i = 0; i < n; i++){
		A[i] = rand()%20000;			
	}

	return A;
}

void imprime_A(int * A, int n){
	int i;

	for(i = 0; i < n; i++){
		printf("%d ", A[i]);
	}

}

void fazExtraiMin(int * A, int n, int k){
	int i;
	for(i = 0; i <= k; i++){
		ExtraiMinPrioridade(A, n);
	}
}