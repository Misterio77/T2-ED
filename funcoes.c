#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"
#include "funcoes.h"

struct _abb {
	no *raiz;
	int altura;
};

//funcao que verifica se a arvore esta vazia.
int arvore_vazia(abb *A) {
	if(A != NULL) {
		if(A->raiz == NULL) return (1);
	}
	return 0;
}

int busca_abb(ABB *A, int item) {
	if(A != NULL){
		if(busca_no(A->raiz, item) != NULL) return(1);
		return(0);
	}
	return(0);
}

//funcao cria uma arvore
abb *criar_arvore() {
	abb *A;
	A = (abb*)malloc(sizeof(abb));
	if (A == NULL) return(NULL);
	printf("arvore foi alocada\n");
	A->raiz = NULL;
	return (A);
}

//funcao insere um item.
void inserir_abb(abb *A, int num) {
	if (A != NULL) {
		inserir_no(A->raiz, num);
	}
	return;
}

//remove um item.
void remove_item(abb *A, int item) {
	if (A != NULL) remover_no(A->raiz, item);
	return;
}

//limpa e remove a arvore
void remove_arvore(abb *A) {
	if (A != NULL) { 
		limpar_no(A->raiz); 
		free(A);
	}
	return;
}
