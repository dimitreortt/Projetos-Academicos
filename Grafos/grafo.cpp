#include "grafo.h"

void Grafo::addVertice(){
	Vertice * novo = new Vertice{};
	Vertice * temp;
    // ListaDeVertices l;

	temp = l.head;
	if(temp == NULL){		//Lista vazia, insere no começo
		l.head = l.tail = novo;
		l.head->id = 1;
	}
	else{					//lista não vazia, insere no fim
		l.tail->prox = novo;
		l.tail->prox->id = l.count + 1;
		l.tail = novo;;
	}
	l.count++;
	printf("Vertice added!\n");
}

void printInfo(Aresta * a){
	printf("%d %d\n", a->info.a, a->info.b);
}

void imprimeArestas(ListaDeArestas a){
	Aresta * temp = a.head;
	printf("Arestas nesse vertice %d\n", a.count);
	if(temp == NULL){
		printf("Este Vertice nao possui arestas\n");
	}
	else{
		while(temp != NULL){
			printInfo(temp);
			temp = temp->prox;
		}
	}
}

void Grafo::listVertices(){
	Vertice * temp = l.head;
	if(temp == NULL){
		printf("Lista Vazia!\n");
	}
	else{
		while(temp != NULL){
			printf("\nVertice %d\n", temp->id);
			imprimeArestas(temp->lista);
			temp = temp->prox;
		}
	}
}

void addAresta1(ListaDeArestas& l, int id, int custo){
	Aresta * novo = new Aresta{id, custo};
	Aresta * temp;
	temp = l.head;
	if(temp == NULL){
		l.head = l.tail = novo;
	}
	else if(l.head->prox == NULL){
		l.head->prox = l.tail = novo;
	}
	else{
		l.tail->prox = novo;
		l.tail = novo;
	}
	l.count++;
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

void Grafo::addAresta(int id, int d, int custo){
	Vertice * v = buscaVertice(l, d);
	Vertice * a = buscaVertice(l, id);
	if(v != NULL && a != NULL){
		addAresta1(v->lista, id, custo);
		addAresta1(a->lista, d, custo);
	}
	else{
		printf("\nImpossivel adicionar tal aresta\n");
	}
}