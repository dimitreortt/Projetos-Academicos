#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "arvores.h"
#define MAX 10
treg * fexecuta(treg reg){
    static treg v[MAX + 1];
    static int pos = 0;
    if (reg.chave == -1){
        pos = 0;
    }else{
        v[pos] = reg;
        pos++;
    }
    return v;
}

void test_insercao_abb(treg * T){
	int i;
	tnode_s * arv;
	treg * vreg;

	cria_arvore_s(&arv);
	assert(arv==NULL);

	for(i = 0; i < MAX; i++){
		insere_arvore_s(&arv, T[i]);
	}
	/*pre_ordem_s(&arv, fexecuta);
	vreg = fexecuta(T[i - 1]);

	for(i = 0; i < MAX; i++){
		printf("%d ", vreg[i].chave);
	}*/
}

void test_insercao_avl(treg * T){
	int i;
	tnode_avl * arv;
	treg * vreg;

	cria_arvore_avl(&arv);
	assert(arv == NULL);

	for(i = 0; i < MAX; i++){
		insere_arvore_avl(&arv, T[i]);
	}

	/*pre_ordem_avl(&arv, fexecuta);
	vreg = fexecuta(T[i - 1]);

	for(i = 0; i < MAX; i++){
		printf("%d ", vreg[i].chave);
	}*/

}

void test_insercao_rb(treg * T){
	int i;
	tarvore * arv;

	arv = rb_construir_arvore(mycmp,imprime);
	for (i = 0; i < MAX; i++){
        rb_insere(arv,&T[i]);
    }
    rb_in_order(arv);
}


int main(){
	int i;
	treg T[MAX];

	srand((unsigned)time(NULL));
	for(i = 0; i < MAX; i++){
		T[i].chave = rand();
		T[i].idade = rand()%80;
	}
	printf("\n");

	test_insercao_abb(T);
	test_insercao_avl(T);
	test_insercao_rb(T);
}