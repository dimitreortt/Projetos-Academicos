//
// OVERVIEW: grafo_depthFirstSearch.cpp
// ========
// Method definition of Grafo::profundidade(),
// corresponding to the Depth First Search (DFS)
// algorithm.
//
// Author(s): Dimitre Ortt
// Last revision: 22/10/2017

#include "grafo.h"

struct no{
	int chave;
	no * prox;
	no(){
		chave = 0;
		prox = NULL;
	}
};

void insere(no ** a, no * b){
	no * temp = *a;
	no * ant = *a;
	if(temp == NULL){
		*a = b;
	}
	else if(temp->chave > b->chave){
		b->prox = temp;
		*a = b;
	}
	else{
		while(temp->prox != NULL && temp->chave < b->chave){
			ant = temp;
			temp = temp->prox;
		}
		if(temp->prox == NULL){
			if(temp->chave > b->chave){
				ant->prox = b;
				b->prox = temp;
			}
			else{
				temp->prox = b;
				b->prox = NULL;
			}
		}
		else{
			ant->prox = b;
			b->prox = temp;
		}
	}
}
void adiciona(no ** resposta, int id){
	no * novo = new no{};
	novo->chave = id;
	novo->prox = NULL;
	insere(resposta, novo);
}

int verifica(int id, no * a){
	no * temp = a;
	while(temp != NULL){
		if(temp->chave == id){
			return 1;
		}
		temp = temp->prox;
	}
	return 0;
}

void imprime(no * a){
	no * temp;
	for(temp = a; temp != NULL; temp = temp->prox){
		printf("%d ", temp->chave);
	}
	printf("\n");
}

void destroi(no ** a){
	no * temp = *a;
	no * lixo;
	while(temp != NULL){
		lixo = temp;
		temp = temp->prox;
		delete(lixo);
		*a = NULL;
	}
}

void copia(no ** a, no ** b){
	no * temp;
	destroi(a);
	for(temp = *b; temp != NULL; temp = temp->prox){
		adiciona(a, temp->chave);
	}
}

void remove(int b, no ** a){

	if (a == NULL){
		return;
	}
	no * temp;
	no * ant;

	if((*a)->chave == b){
		temp = *a;
		*a = (*a)->prox;
		delete temp;
	}
	else{
		temp = (*a)->prox;
		ant = *a;
		while(temp != NULL && temp->chave != b){
			temp = temp->prox;
			ant = ant->prox;
		}
		if(temp != NULL){
			ant->prox = temp->prox;
			delete temp;
		}
	}

}

Vertice * buscaVertice(ListaDeVertices l, int id){
	Vertice * temp = l.head;
	while(temp != NULL && temp->id != id){
		temp = temp->prox;
	}
	if(temp == NULL){
		return NULL;
	}
	else{
		return temp;
	}
}

void Grafo::profundidade(){
	int C, E, L, P, X, Y;
	int i;
	no * resposta = NULL;
	no * resposta2 = NULL;
	no * temp1;
	Aresta * temp;
	int count = 0;

	while(1){
		scanf("%d %d %d %d", &C, &E, &L, &P);
		if(!C & !E & !L & !P){
			break;
		}
		count++;
		for(i = 0; i < C; i++){
			addVertice();
		}
		for(i = 0; i < E; i++){
			scanf("%d %d", &X, &Y);
			addAresta(X, Y, 1);
		}

		Vertice * v = buscaVertice(l, L);
		if(v != NULL){
			adiciona(&resposta, v->id);
		}
		else{
			return;
		}
		for(i = 0; i < P; i++){
			for(temp1 = resposta; temp1 != NULL; temp1 = temp1->prox){
				v = buscaVertice(l, temp1->chave);
				for(temp = v->lista.head; temp != NULL; temp = temp->prox){
					if(!verifica(temp->info.a, resposta2)){
						adiciona(&resposta2, temp->info.a);
					}
				}
			}
			copia(&resposta, &resposta2);
		}
		remove(L, &resposta2);
		printf("Teste %d\n", count);
		imprime(resposta2);
		printf("\n");

	C = E = L = P = X = Y = 0;
	i = 0;
	resposta = NULL;
	resposta2 = NULL;
	temp1 = NULL;
	temp = NULL;
	}
}