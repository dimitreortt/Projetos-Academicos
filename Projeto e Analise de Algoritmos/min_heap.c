#include "trabalho.h"

/*void troca(int * a, int *b){
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}*/

int esq(int i){
	return 2*i + 1;
}

int dir(int i){
	return 2*(i + 1);
}

int pai(int i){
	return i/2;
}

void Desce(int * S, int tam, int i){ 
	int menor;
	int e = esq(i);
	int d = dir(i);
	if (e < tam && S[e] < S[i]){
		menor = e;
	} 
	else{ 
		menor = i;
	}
	if (d < tam && S[d] < S[menor]){
		menor = d;
	} 
	if (menor != i){
		troca(&S[i], &S[menor]);
		Desce(S, tam, menor);
	} 
	
}

int ExtraiMinPrioridade(int * S, int tam){
	int ret = 0;
	if(S != NULL){
		ret = S[0];
		if(tam == 1){
			S = NULL;
		}
		else{
			S[0] = S[tam - 1];
			Desce(S, tam - 1, 0);
		}
		return ret;
	}
}

void ConstroiMinHeap(int * S, int tam){
	int i;
	for(i = tam/2 - 1; i >= 0; i--){
		Desce(S, tam, i);
	}
	for(i = 0; i < tam; i++){
		printf("%d ", S[i]);
	}
	printf("n\n");
}