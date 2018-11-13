#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"

struct _item{
	int cod;
	char nome[32];
}

struct _no {
	item *prod;
	struct _no *esq, *dir;
};

int cod_item(item prod){
	return(prod->cod);
}

//funcao que aloca um no
no *criar_no() {
	no *B;
	B = (no*)malloc(sizeof(no));
	if(B == NULL) return (NULL);
	B->esq = NULL;
	B->dir = NULL;
	printf("no foi alocado\n");
	return (B);
}

//funcao que insere um item em um no ja alocado
void inserir_item(no *B, item prod) {
	if(B != NULL) {
		B->prod = prod;
		return;
	}
	printf("B nao foi alocado corretamente\n");
	return;
}

//funcao que insere um item em um no ainda nao alocado
no *inserir_no(no *B, item prod) {
	
	if(B == NULL) {
		B = criar_no();
		if(B != NULL) {
			B->prod = prod;
			return (B);
		}
		return (NULL);
	}
	if(cod_item(prod) < cod_item(B->prod)) B->esq = inserir_no(B->esq, prod);
	if(cod_item(prod) > cod_item(B->prod)) B->dir = inserir_no(B->dir, prod);
	return (B);
}

//funcao que busca um no tendo um item como referencia
no *busca_no(no *raiz, int chave) {
	while (raiz != NULL && cod_item(raiz->prod) != chave) {
		if (chave < cod_item(raiz->prod)) raiz = raiz->esq;
		else raiz = raiz->dir;
	}
	return(raiz);
}

//funcao que diz a altura de um no (caminho mais longo ate o no). 
void altura_no(no *raiz, int *max, int atual) {
	if (raiz != NULL) {
		atual++;
		if (atual > (*max)) (*max) = atual;
		altura_no(raiz->esq, max, atual);
		altura_no(raiz->dir, max, atual);
	}
	return;
}

//remove um no que nao tem filhos
void remove_c1(no *ant, no *rem) {
	if ((cod_item(ant->prod)) > (cod_item(rem->prod))) ant->esq = NULL;
	else ant->dir = NULL;
	free(rem);
	return;
}

//remove um no que tem apenas um filho.
void remove_c2(no *ant, no *rem) {
	if ((cod_item(ant->prod)) > (cod_item(rem->prod))) {
		if(rem->esq != NULL) ant->esq = rem->esq;
		else ant->esq = rem->dir;
	}
	else if(rem->esq != NULL) ant->dir = rem->esq;
	else ant->dir = rem->dir;
	free(rem);
	return;
}

//remove um no que tem os dois filhos.
void remove_c3(no *ant, no *rem) {
	no *aux = (no*)malloc(sizeof(no));
	if(aux == NULL) return;
	aux = rem->esq;
	ant = rem;
	if (aux->dir == NULL) {
		rem->prod = aux->prod;
		rem->esq = aux->esq;
		free(aux);
		return;
	}
	while(aux->dir != NULL) {
		ant = aux;
		aux = aux->dir;
	}
	rem->prod = aux->prod;
	ant->dir = aux->esq;
	free(aux);
	return;
}

//remove um no
void remover_no(no *raiz, int chave) {
	no *aux;
	aux = (no*)malloc(sizeof(no));
	if (aux != NULL) {
		while (raiz != NULL && cod_item(raiz->prod) != chave) {
			aux = raiz;
			if (chave < cod_item(raiz->prod)) raiz = raiz->esq;
			else raiz = raiz->dir;
		}
	}
	if (raiz == NULL) return;
	if (raiz->esq == NULL && raiz->dir == NULL) remove_c1(aux, raiz);
	else if ((raiz->esq != NULL) ^ (raiz->dir != NULL)) remove_c2(aux, raiz);
	else remove_c3(aux, raiz);
	return;
}

//remove arvove.
void limpar_no(no *raiz) {
	if (raiz != NULL) {
		limpar_no(raiz->esq);
		limpar_no(raiz->dir);
		free(raiz);
	}
	return;
}
