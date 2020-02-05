#include "trabalho.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 200

int main(){
	int A[MAX];
	int i, n, k;
	clock_t start, end, ant;
	start = clock();
	srand((unsigned)time(NULL));

	for(n = 10; n < MAX + 1; n += 10){
		k = rand()%n;
		printf("k : %d\n", k);
		
		le_A(A, n);

		imprime_A(A, n);

		printf("rs %d\n", RandomizedSelect(A, 0, n - 1, k));
		printf("quick: %d\n", quicksort(A, n, k));
		imprime_A(A, n);

		printf("a\n");
		ConstroiMinHeap(A, n);

		fazExtraiMin(A, n, k);	/*Extrai min prioridade k + 1 vezes*/

		imprime_A(A, n - k - 1);

		printf("G\n");
	}

	

	
	return 0;
}