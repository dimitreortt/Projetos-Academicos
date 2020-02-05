//
// OVERVIEW: Driver to run functionalities
// implemented.
//
// Author(s): Dimitre Ortt
// Last revision: 22/10/2017

#include "grafo.h"

int main(){
	Grafo * grafo = new Grafo{};
	grafo->profundidade();
	grafo->djikstra();
	return 0;	
}