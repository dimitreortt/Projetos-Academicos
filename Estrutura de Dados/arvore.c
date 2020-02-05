#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

int cmpfunc(const void *a, const void *b){
    return (*(treg *)a).chave - (*(treg *)b).chave ;
}

void cria_arvore_s(tnode_s ** parv){
    *parv = NULL;
}
void insere_arvore_s(tnode_s ** parv,treg reg){
    if (*parv == NULL){
        *parv = (tnode_s *) malloc(sizeof(tnode_s));
        (*parv)->reg = reg;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
    }else if(cmpfunc(&((*parv)->reg), &reg)>0){
        insere_arvore_s(&(*parv)->esq,reg);
    }else{
        insere_arvore_s(&((*parv)->dir),reg);
    }
}

void pre_ordem_s(tnode_s **parv, treg * (*myfunc)(treg)){
    if (*parv != NULL){
        myfunc((*parv)->reg);
        pre_ordem_s(&(*parv)->esq,myfunc);
        pre_ordem_s(&(*parv)->dir,myfunc);
    }
}
void in_ordem_s(tnode_s **parv, treg * (*myfunc)(treg)){
    if (*parv != NULL){
        in_ordem_s(&(*parv)->esq,myfunc);
        myfunc((*parv)->reg);
        in_ordem_s(&(*parv)->dir,myfunc);
    }
}
void pos_ordem_s(tnode_s **parv, treg * (*myfunc)(treg)){
    if (*parv != NULL){
        pos_ordem_s(&(*parv)->esq,myfunc);
        pos_ordem_s(&(*parv)->dir,myfunc);
        myfunc((*parv)->reg);
    }
}

tnode_s ** busca_no_s(tnode_s **parv, treg reg){
    tnode_s ** ret;
    int cmp;
    if (*parv == NULL)
        ret = NULL;
    else{
        cmp = cmpfunc(&(*parv)->reg,&reg);
        if (cmp == 0){
            ret = parv;
        }else if (cmp > 0){
            ret = busca_no_s(&((*parv)->esq),reg);
        }else{
            ret = busca_no_s(&((*parv)->dir),reg);
        }
    }
    return ret;
}

void apaga_arvore_s(tnode_s **parv){
    if (*parv != NULL){
        apaga_arvore_s(&(*parv)->esq);
        apaga_arvore_s(&(*parv)->dir);
        free(*parv);
        *parv = NULL;
    }
}

tnode_s ** percorre_esq_s(tnode_s ** arv){
    tnode_s * aux = *arv;
    if (aux->esq == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
    }
}

int apaga_node_s(tnode_s **parv,treg reg){
    int ret = 0;
    tnode_s ** raiz;
    tnode_s * aux;
    tnode_s * auxraiz;
    tnode_s ** filho;
    /*busca node*/
    raiz = busca_no_s(parv,reg);
    
    if (raiz == NULL){
        ret = 0;
    }else if ((*raiz)->dir == NULL){
        /*trata caso degenerado esq*/
        aux = *raiz;
        *raiz = aux->esq;
        free(aux);
    }else{
        /*remove direita esquerda*/
        filho = percorre_esq_s(&(*raiz)->dir);
        aux = *filho;
        *filho = aux->dir;

        aux->esq = (*raiz)->esq;
        aux->dir = (*raiz)->dir;
        auxraiz = *raiz;
        *raiz = aux;
        free(auxraiz);
    }
    return ret;

}
