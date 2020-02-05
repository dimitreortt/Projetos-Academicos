#include <stdio.h>
#include <time.h>

void QuickSort(int p, int r, int * A);
void fazExtraiMin(int * A, int n, int k);
void imprime_A(int * A, int n);
int * le_A(int * A, int n);
void ConstroiMinHeap(int * S, int tam);
int ExtraiMinPrioridade(int * S, int tam);
int RandomizedSelect(int * A, int p, int r, int k);

void troca(int * a, int *b);