#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

int cmpfunc_avl(const void *a, const void *b){
    return (*(treg *)a).chave - (*(treg *)b).chave ;
}

tnode_avl ** percorre_esq_avl(tnode_avl ** arv){
    tnode_avl * aux = *arv;
    if (aux->esq == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
    }
}

void cria_arvore_avl(tnode_avl ** parv){
    *parv = NULL;
}
void insere_arvore_avl(tnode_avl ** parv,treg reg){
    if (*parv == NULL){
        *parv = (tnode_avl *) malloc(sizeof(tnode_avl));
        (*parv)->reg = reg;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
    }else if(cmpfunc_avl(&((*parv)->reg), &reg)>0){
        insere_arvore_avl(&(*parv)->esq,reg);
    }else{
        insere_arvore_avl(&((*parv)->dir),reg);
    }
}
int max(int a,int b){
    return a>b?a:b;
}

int altura(tnode_avl *arv){
    int ret;
    if (arv==NULL){
        ret = 0;
    }else{
        ret = arv->h;
    }
    return ret;
}
void RE_avl(tnode_avl **parv){
    tnode_avl * y = *parv;
    tnode_avl * x = y->dir;
    tnode_avl * A = y->esq;
    tnode_avl * B = x->esq;
    tnode_avl * C = x->dir;

    y->dir = B; 
    y->esq = A;
    x->dir = C;
    x->esq = y;
    *parv = x;
    y->h = max(altura(A),altura(B)) +1;
    x->h = max(altura(y),altura(C))+1;

}
void RD_avl(tnode_avl **parv){
    tnode_avl * x = *parv;
    tnode_avl * y = x->esq;
    tnode_avl * A = y->esq;
    tnode_avl * B = y->dir;
    tnode_avl * C = x->dir;

    x->dir = C; 
    x->esq = B;
    y->esq = A;
    y->dir = x;
    *parv = y;

    x->h = max(altura(B),altura(C)) +1;
    y->h = max(altura(A),altura(x)) +1;
}


void rebalancear_avl(tnode_avl **parv){
    int fb;
    int fbf;
    tnode_avl *filho;


    fb = altura((*parv)->esq) - altura((*parv)->dir);
    if (fb == -2){ /*--> -->*/
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir); 
        if (fbf <= 0){ /* ---> */
            RE_avl(parv);
        }else{ /* <-- */
            RD_avl(&(*parv)->dir);
            RE_avl(parv);
        }
    }else if (fb == 2){ /*<-- <--*/
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir); 
        if (fbf >= 0){ /* <-- */
            RD_avl(parv);
        }else{ /* ->*/
            RE_avl(&(*parv)->esq);
            RD_avl(parv);
        }
    }

}


void insere_avl(tnode_avl ** parv,treg reg){
    if (*parv == NULL){
        *parv = (tnode_avl *) malloc(sizeof(tnode_avl));
        (*parv)->reg = reg;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
        (*parv)->h = 1;

    }else if(cmpfunc_avl(&((*parv)->reg), &reg)>0){
        insere_avl(&(*parv)->esq,reg);
    }else{
        insere_avl(&(*parv)->dir,reg);
    }
    (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
    rebalancear_avl(parv);
}


void pre_ordem_avl(tnode_avl **parv, treg * (*myfunc)(treg)){
    if (*parv != NULL){
        myfunc((*parv)->reg);
        pre_ordem_avl(&(*parv)->esq,myfunc);
        pre_ordem_avl(&(*parv)->dir,myfunc);
    }
}
void in_ordem_avl(tnode_avl **parv, treg * (*myfunc)(treg)){
    if (*parv != NULL){
        in_ordem_avl(&(*parv)->esq,myfunc);
        myfunc((*parv)->reg);
        in_ordem_avl(&(*parv)->dir,myfunc);
    }
}
void pos_ordem_avl(tnode_avl **parv, treg * (*myfunc)(treg)){
    if (*parv != NULL){
        pos_ordem_avl(&(*parv)->esq,myfunc);
        pos_ordem_avl(&(*parv)->dir,myfunc);
        myfunc((*parv)->reg);
    }
}


tnode_avl ** apaga_avl(tnode_avl **parv, treg reg){
    tnode_avl ** ret;
    tnode_avl *aux;
    tnode_avl **sucessor;
    int cmp;
    if (*parv == NULL)
        ret = NULL;
    else{
        cmp = cmpfunc_avl(&(*parv)->reg,&reg);
        if (cmp > 0){
            ret = apaga_avl(&((*parv)->esq),reg);
        }else if (cmp < 0){
            ret = apaga_avl(&((*parv)->dir),reg);
        }else{ /*achou!! remove o registro*/
            /*node folha*/
            if ((*parv)->esq == NULL && (*parv)->dir == NULL){
                free(*parv);
                *parv = NULL;
            }else if ((*parv)->esq == NULL || (*parv)->dir == NULL){
                /*tem um filho*/
                aux = *parv;
                if ((*parv)->esq == NULL){
                    *parv = (*parv)->dir;
                }else{
                    *parv = (*parv)->esq;
                }
                free(aux);
            }else{
                /*tem dois filhos*/
                sucessor = percorre_esq_avl(&(*parv)->dir);
                (*parv)->reg = (*sucessor)->reg;
                ret = apaga_avl(&(*parv)->dir,(*sucessor)->reg); 
            }
        }
        if (*parv != NULL){
            (*parv)->h = max(altura((*parv)->esq),altura((*parv)->dir)) + 1;
            rebalancear_avl(parv);
        }
        ret = parv;

    }
    return ret;
}




tnode_avl ** busca_no_avl(tnode_avl **parv, treg reg){
    tnode_avl ** ret;
    int cmp;
    if (*parv == NULL)
        ret = NULL;
    else{
        cmp = cmpfunc_avl(&(*parv)->reg,&reg);
        if (cmp == 0){
            ret = parv;
        }else if (cmp > 0){
            ret = busca_no_avl(&((*parv)->esq),reg);
        }else{
            ret = busca_no_avl(&((*parv)->dir),reg);
        }
    }
    return ret;
}

void apaga_arvore_avl(tnode_avl **parv){
    if (*parv != NULL){
        apaga_arvore_avl(&(*parv)->esq);
        apaga_arvore_avl(&(*parv)->dir);
        free(*parv);
        *parv = NULL;
    }
}



int apaga_node_avl(tnode_avl **parv,treg reg){
    int ret = 0;
    tnode_avl ** raiz;
    tnode_avl * aux;
    tnode_avl * auxraiz;
    tnode_avl ** filho;
    /*busca node*/
    raiz = busca_no_avl(parv,reg);
    
    if (raiz == NULL){
        ret = 0;
    }else if ((*raiz)->dir == NULL){
        /*trata caso degenerado esq*/
        aux = *raiz;
        *raiz = aux->esq;
        free(aux);
    }else{
        /*remove direita esquerda*/
        filho = percorre_esq_avl(&(*raiz)->dir);
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
