//
// OVERVIEW: grafo.h
// ========
// Class definition for a Graph (Grafo),
// includes the definitions of:
// Pair (Par),
// Edge (Aresta), 
// EdgesList (ListaDeArestas),
// Vertex (Vertice) and
// VertexList (ListaDeVertices).
//
// Author(s): Dimitre Ortt
// Last revision: 22/10/2017

#include <stdio.h>
#include <climits>

struct Par{

	int a;
	int b;

	Par(){
		a = 0;
		b = 0;
	}
};

struct Aresta{

	Par info;
	Aresta * prox;
	Aresta(){
		prox = NULL;
	}
	Aresta(int a, int b){
		info.a = a;
		info.b = b;
		prox = NULL;
	}
};

struct ListaDeArestas{

	Aresta * head;
	Aresta * tail;
	int count;

	ListaDeArestas(){
		head = NULL;
		tail = NULL;
		count = 0;
	}

};

struct Vertice{

	int dist;
	int id;
	ListaDeArestas lista;
	Vertice * prox;
	Vertice(){
		id = 0;
		dist = INT_MAX;
		prox = NULL;
	}
};

struct ListaDeVertices{

	Vertice * head;
	Vertice * tail;
	int count;

	ListaDeVertices(){
		head = NULL;
		tail = NULL;
		count = 0;
	}
};

class Grafo{
	ListaDeVertices l;
public:
	void addVertice();		
	void listVertices();
	void addAresta(int, int, int); //(v1, v2, custo)
	int djikstra();
	void profundidade();
};

Vertice * buscaVertice(ListaDeVertices, int);




