//
// OVERVIEW: arvores.h
// ========
// Struct definitions for AVL, 
// Red-black and ABB trees.
//
// Author(s): Dimitre Ortt
// Last revision: 17/11/2017

#ifndef ARVORES_H
#define ARVORES_H

typedef int tchave;
typedef struct{
    tchave chave;
    int idade;
}treg;

typedef struct node_simples{
    treg reg;
    struct node_simples * esq;
    struct node_simples * dir;
}tnode_s;

typedef struct node_avl{
    treg reg;
    struct node_avl * esq;
    struct node_avl * dir;
    struct node_avl * pai;     
    int h;
}tnode_avl;

typedef struct {
    treg v[100];
    int last;
}tpilha;


/*******    ARVORE.H   ****************/
void cria_arvore_s(tnode_s ** parv);
void insere_arvore_s(tnode_s ** parv,treg reg);
void pre_ordem_s(tnode_s **parv, treg * (*myfunc)(treg));
void in_ordem_s(tnode_s **parv, treg * (*myfunc)(treg));
void pos_ordem_s(tnode_s **parv, treg * (*myfunc)(treg));
tnode_s ** busca_no_s(tnode_s **parv, treg reg);
void apaga_arvore_s(tnode_s **parv);
int apaga_node_s(tnode_s **parv,treg reg);
/************************************/


/**********    AVL.H    ****************/
void cria_arvore_avl(tnode_avl ** parv);
void insere_arvore_avl(tnode_avl ** parv,treg reg);
void pre_ordem_avl(tnode_avl **parv, treg * (*myfunc)(treg));
void in_ordem_avl(tnode_avl **parv, treg * (*myfunc)(treg));
void pos_ordem_avl(tnode_avl **parv, treg * (*myfunc)(treg));
tnode_avl ** busca_no_avl(tnode_avl **parv, treg reg);
void apaga_arvore_avl(tnode_avl **parv);
int apaga_node_avl(tnode_avl **parv,treg reg);

void insere_avl(tnode_avl ** parv,treg reg);
tnode_avl ** apaga_avl(tnode_avl ** parv,treg reg);
/***************************************/




/******************************************************/
/***************REDBLACK.H*****************************/
typedef struct node_rb{
    treg * reg;
    int cor;
    struct node_rb * dir;
    struct node_rb * esq;
    struct node_rb * pai;
}tnode_rb;

typedef struct arv{
    int (*compara)(const void *a, const void *b);
    void (*imprime_reg)(void *a);
    tnode_rb * raiz;
}tarvore;

/* publico */
enum cor {VERMELHO,PRETO};
enum direcao {DDIR,DESQ};


tarvore * rb_construir_arvore(int (*compara)(const void *, const void *), 
                         void (*imprime_reg)(void *a));

int  rb_insere(tarvore * parv, void * x);
void rb_in_order(tarvore *parv);
void rb_destroi(tarvore *parv);
void rb_remove(tarvore *parv, treg * reg);

int mycmp(const void *a, const void *b);
void imprime(void *a);

#endif 