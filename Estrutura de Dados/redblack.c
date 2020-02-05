#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

int mycmp(const void *a, const void *b){
    return ((treg *)a)->chave - ((treg *)b)->chave;
}

void imprime(void *a){
    printf("endre %p\n",a);
    printf("chave %d\n",((tnode_rb *)a)->reg->chave);
    printf("idade %d\n",((tnode_rb *)a)->reg->idade);
    printf("cor %d\n\n", ((tnode_rb *)a)->cor);                   //###############################################

}

tarvore * rb_construir_arvore(int (*compara)(const void *, const void *), 
                         void (*imprime_reg)(void *a)){
    tarvore * parv;
    parv = (tarvore *)malloc(sizeof(tarvore));
    parv->compara = compara;
    parv->imprime_reg = imprime_reg;
    parv->raiz = NULL;
    return parv;
}


int obtem_cor(tnode_rb *parv){
    if (parv == NULL)
        return PRETO;
    else 
        return parv->cor;
}

void RD(tnode_rb  **parv){ /*rotacao direita*/
    tnode_rb *x = *parv;
    tnode_rb *y = x->esq;
    tnode_rb *a = y->esq;
    tnode_rb *b = y->dir;
    tnode_rb *c = x->dir; 
    y->esq = a;
    y->dir = x;
    x->esq = b;
    x->dir = c;
    *parv = y;

    if (a != NULL ) a->pai = y;
    if (b != NULL ) b->pai = x;
    if (c != NULL ) c->pai = x;
    y->pai = x->pai;
    x->pai = y;
}

void RE(tnode_rb **parv){
    tnode_rb *y = *parv;
    tnode_rb *x = y->dir;
    tnode_rb *a = y->esq;
    tnode_rb *b = x->esq;
    tnode_rb *c = x->dir; 
    y->esq = a;
    y->dir = b;
    x->esq = y;
    x->dir = c;
    *parv = x;

    if (a != NULL ) a->pai = y;
    if (b != NULL ) b->pai = y;
    if (c != NULL ) c->pai = x;

    x->pai = y->pai;
    y->pai = x;
}




int procura_vermelho_duplo(tnode_rb *pai, int *filho_seta, tnode_rb **filho){
    int vermelho_duplo = 0;
    if (pai != NULL){
        if (obtem_cor(pai->esq) == VERMELHO){
            *filho_seta = DESQ;
            *filho = pai->esq;
            vermelho_duplo = 1;

        }else if (obtem_cor(pai->dir) == VERMELHO){
            *filho_seta = DDIR;
            *filho = pai->dir;
            vermelho_duplo = 1;
        }
    }
    return vermelho_duplo;

}



void rebalancear(tnode_rb **parv){
    int vermelho_duplo = 0;
    int pai_seta;
    int filho_seta;
     
    tnode_rb *tio;
    tnode_rb *pai=NULL;
    tnode_rb *avo;
    tnode_rb *filho;

    avo = *parv;
    vermelho_duplo = 0;
    if (obtem_cor(avo->esq) == VERMELHO){ 
        pai = avo->esq;
        tio = avo->dir;
        pai_seta = DESQ;
        vermelho_duplo = procura_vermelho_duplo(pai,&filho_seta, &filho);

    }
    if (obtem_cor(avo->dir) == VERMELHO && !vermelho_duplo){
        pai = avo->dir;
        tio = avo->esq;
        pai_seta = DDIR;
        vermelho_duplo = procura_vermelho_duplo(pai,&filho_seta, &filho);
    }
    
    if (vermelho_duplo){ 
        if (obtem_cor(tio) == VERMELHO){ /* CASO 1: tio vermelho RECOLORIR */
            tio->cor = PRETO;
            pai->cor = PRETO;
            avo->cor = VERMELHO;
        }else{ 
            /*CASO 2: tio preto, REBALANCEAR*/
            if (pai_seta == DDIR){
                if (filho_seta == DESQ){
                    RD(&avo->dir);
                }
                RE(parv);
            }else if (pai_seta == DESQ){
                if (filho_seta == DDIR){
                    RE(&avo->esq);
                }
                RD(parv);
            }
            (*parv)->cor = PRETO;
            (*parv)->esq->cor = VERMELHO;
            (*parv)->dir->cor = VERMELHO;
        }
    }
}


int _insere(tarvore * parv, tnode_rb ** pnode,treg * reg){
    int lcmp;
    int ret = 1;
    if (*pnode == NULL){
        *pnode = (tnode_rb *)malloc(sizeof(tnode_rb));
        if (*pnode == NULL)
            ret = 0;
        else{
            (*pnode)->reg = reg;
            (*pnode)->esq = NULL;
            (*pnode)->dir = NULL;
            (*pnode)->pai = NULL;
            (*pnode)->cor = VERMELHO;
        }
    }else{
        lcmp = parv->compara((*pnode)->reg,reg); 
        if (lcmp >= 0){
            ret = _insere(parv,&(*pnode)->esq,reg);
            (*pnode)->esq->pai = *pnode;
        }else if (lcmp < 0){
            ret = _insere(parv,&(*pnode)->dir,reg);
            (*pnode)->dir->pai = *pnode;
        }
        rebalancear(pnode);
    }
    return ret;
}


void _in_order(tarvore *parv,tnode_rb * pnode){
    if (pnode != NULL){
        _in_order(parv,pnode->esq);
        parv->imprime_reg(pnode);    //############################################
        _in_order(parv,pnode->dir);
    }
}

void rb_in_order(tarvore *parv){
    _in_order(parv,parv->raiz);
}

void _destroi(tnode_rb * pnode){
    if (pnode != NULL){
        _destroi(pnode->esq);
        _destroi(pnode->dir);
        free(pnode);
    }
}

void rb_destroi(tarvore *parv){
    _destroi(parv->raiz);
    parv->raiz = NULL;
}

tnode_rb ** pp_node(tarvore *arv,tnode_rb *node){ /* ponteiro de ponteiro do no*/
    tnode_rb * pai;
    tnode_rb **ret;
    if (node == arv->raiz){
        ret= &(arv->raiz);
    }else{
        pai = node->pai;
        if (pai->esq == node)
            ret = &(pai->esq);
        else if (pai->dir == node){
            ret = &(pai->dir);
        }else{
            printf("ERROR!! pp_node");
        }
    }
    return ret;
}


void remove_fixup(tarvore *parv, tnode_rb *x){
    tnode_rb *raiz = parv->raiz;
    tnode_rb *irmao;
    while(obtem_cor(x) == PRETO && (raiz != x)){
        if (x == x->pai->esq){
            irmao = x->pai->dir;
            if (obtem_cor(irmao) == VERMELHO){  /* caso 1: irmao vermelho*/
                irmao->cor = PRETO;
                x->pai->cor = VERMELHO;
                RE(pp_node(parv,x->pai));
                irmao = x->pai->dir;
            }
            if ( obtem_cor(irmao->dir) == PRETO &&  obtem_cor(irmao->esq) == PRETO){ /* caso 2: irmao preto*/
                irmao->cor = VERMELHO;
                x = x->pai;
            }else {
                if (obtem_cor(irmao->dir) == PRETO) {
                    irmao->esq->cor = PRETO;
                    irmao->cor = VERMELHO;
                    RD(pp_node(parv,irmao));
                    irmao = x->pai->dir;
                }
                irmao->cor = x->pai->cor;
                x->pai->cor = PRETO;
                irmao->dir->cor = PRETO;
                RE(pp_node(parv,x->pai));
                x = raiz;
            }
        }else{
            irmao = x->pai->esq;
            if (obtem_cor(irmao) == VERMELHO){  /* caso 1: irmao vermelho*/
                irmao->cor = PRETO;
                x->pai->cor = VERMELHO;
                RD(pp_node(parv,x->pai));
                irmao = x->pai->esq;
            }
            if ( obtem_cor(irmao->esq) == PRETO &&  obtem_cor(irmao->dir) == PRETO){ /* caso 2: irmao preto*/
                irmao->cor = VERMELHO;
                x = x->pai;
            }else {
                if (obtem_cor(irmao->esq) == PRETO) {
                    irmao->dir->cor = PRETO;
                    irmao->cor = VERMELHO;
                    RE(pp_node(parv,irmao));
                    irmao = x->pai->esq;
                }
                irmao->cor = x->pai->cor;
                x->pai->cor = PRETO;
                irmao->esq->cor = PRETO;
                RD(pp_node(parv,x->pai));
                x = raiz;
            }

        }
    }
    x->cor = PRETO;
}

tnode_rb * percorre_esq(tnode_rb * arv){
    tnode_rb * aux = arv;
    if (aux->esq == NULL){
        return arv;
    }else{
        while (aux->esq->esq != NULL)
            aux = aux->esq;
        return aux->esq;
    }
}
int folha(tnode_rb *arv){
    return (arv->esq == NULL && arv->dir == NULL)?1:0;
}


int _remove(tarvore *parv, tnode_rb *pnode, treg * reg){
    int ret = 1;
    int lcmp;

    tnode_rb *sucessor,*x;
    if (pnode == NULL){ /*not found key*/
        ret = 0;
    }else{
        lcmp = parv->compara(pnode->reg,reg);
        if (lcmp >0){
            ret = _remove(parv,pnode->esq,reg);
        }else if (lcmp < 0){
            ret = _remove(parv,pnode->dir,reg);
        }else{ /*achou!!*/
            if (pnode->dir != NULL){
                /*tem sucessor*/
                sucessor = percorre_esq(pnode->dir);
                pnode->reg = sucessor->reg;
                ret = _remove(parv,pnode->dir,sucessor->reg); 
            }else if (pnode->esq != NULL && pnode->pai == NULL){ /* caso patologico: tem filho a esquerda mas a direita esta vazio*/
                    parv->raiz = pnode->esq;        
                    free(pnode);
                    parv->raiz->cor = PRETO;
            }else if(pnode->esq != NULL){
                pnode->reg = pnode->esq->reg;
                _remove(parv, pnode->esq, pnode->reg);
            }else if (folha(pnode)){
                x = pnode;
                if (x != parv->raiz){
                    if (obtem_cor(x) == PRETO)
                        remove_fixup(parv,x);
                    if (x->pai->esq == x){
                        x->pai->esq = NULL;
                    }else{
                        x->pai->dir = NULL;
                    }
                }else{ /* remocao no raiz*/
                    parv->raiz = NULL;
                }
                free(x);
            }
        }
    }
    return ret;
    
}

void rb_remove(tarvore *parv, treg * reg){
    _remove(parv,parv->raiz,reg);
}



int rb_insere(tarvore * parv, void * reg){
    int ret;
    ret = _insere(parv,&(parv->raiz),reg);
    parv->raiz->cor = PRETO;
    return ret;
}




