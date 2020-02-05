//
// OVERVIEW: grafo_djikstra.cpp
// ========
// Method definition of Grafo::djikstra(),
// which is the implementation of the 
// Djikstra Algorithm in Graphs.
//
// Author(s): Dimitre Ortt
// Last revision: 22/10/2017

#include "grafo.h"
#include <stdio.h>
#include <cstdlib>

int verifica(Vertice * v, Vertice ** S, int tam){
	for (int i = 0; i < tam; i++){
		if((S[i]) == v)
			return 1;
	}
	return 0;
}

Vertice * buscaMinVertice(Vertice ** S, ListaDeVertices l, int tam){
	int min = INT_MAX;
	Vertice * v;
	Vertice * guarda = NULL;
	for(v = l.head; v != NULL; v = v->prox){
		if(!verifica(v, S, tam)){
			if(v->dist < min){
				min = v->dist;
				guarda = v;
			}
		}
	}
	return guarda;
}

int min(int a, int b){
	if(a < b)
		return a;
	else
		return b;
}

int djikstra1(ListaDeVertices l){

	Vertice * a = l.head;
	Vertice * b = l.tail;

	Vertice ** S = (Vertice **) calloc(l.count, sizeof(Vertice*));
	Vertice * v;
	Aresta * aresta;
	Vertice * aux2;
	Vertice * temp;

	a->dist = 0;
	printf("%d %d d\n", a->dist, b->dist);

	S[0] = a;
	for(aresta = a->lista.head; aresta != NULL; aresta = aresta->prox){
		v = buscaVertice(l, aresta->info.a);
		v->dist = aresta->info.b;
		printf("dist %d\n", v->dist);
	}	
	for(int i = 1; i < l.count; i++){
		for(temp = l.head; temp != NULL; temp = temp->prox){
			printf("temp->id: %d, temp->dist: %d\n", temp->id, temp->dist);
		}
		v = buscaMinVertice(S, l, i);
		if(v != NULL){
			S[i] = v;
			printf("\nO id do V v->id %d\n\n", v->id);
			for(aresta = v->lista.head; aresta != NULL; aresta = aresta->prox){
				aux2 = buscaVertice(l, aresta->info.a);
				aux2->dist = min(v->dist + aresta->info.b, aux2->dist);
				printf("aux2->id %d, aux2->dist%d\n", aux2->id, aux2->dist);
			}
		}
		else{
			printf("fim djikstra aqui\n");
		}
	}
	return b->dist;
}

/*este método lê um grafo e responde com um inteiro indicando o caminho minimo
entre o primeiro e o ultimo vertices*/
int Grafo::djikstra(){
	int i, N, M, S, T, B;
	scanf("%d %d", &N, &M);
	for(i = 0; i < N + 2; i++){
		addVertice();
	}//listVertices();
	for(i = 0; i < M; i++){
		scanf("%d %d %d", &S, &T, &B);
		addAresta(S, T, B);
	}	//listVertices();
	return djikstra1(l);
}