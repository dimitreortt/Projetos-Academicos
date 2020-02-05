#include "trabalho.h"
#include <time.h>
#define MAX 200

void troca(int * a, int *b){
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void Quick(int vetor[10], int inicio, int fim){
	int pivo, aux, i, j, meio;
	i = inicio;
	j = fim;
	meio = (int) ((i + j) / 2);
	pivo = vetor[meio];
	do{
		while (vetor[i] < pivo) i = i + 1; 
		while (vetor[j] > pivo) j = j - 1;
		if(i <= j){
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
			i = i + 1;
			j = j - 1;
		}
	}while(j > i);
	if(inicio < j) Quick(vetor, inicio, j);
	if(i < fim) Quick(vetor, i, fim);
}

int quicksort(int A[MAX], int length, int k){
	Quick(A, 0, length - 1);
	printf("%d\n", A[0]);
	if (k <= length)
		return A[k];
}