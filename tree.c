#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "tree.h"

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

int busca_abb(abb *A, int item) {
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
	if (A == NULL) {
		printf("\narvore nao alocada");
		return(NULL);
		}
	A->raiz = NULL;
	return (A);
}

//funcao insere um item.
void inserir_abb(abb *A, int item) {
	if (A != NULL) {
		if (arvore_vazia(A)) {
			A->raiz = criar_no();
			inserir_item(A->raiz, item);
		}
		else inserir_no(A->raiz, item);
	}
	return;
}

//remove um item.
void remover_item(abb *A, int item) {
	if (A != NULL) remover_no(A->raiz, item);
	return;
}

//limpa e remove a arvore
void remover_arvore(abb *A) {
	if (A != NULL) { 
		limpar_no(A->raiz); 
		free(A);
	}
	return;
}

//imprime itens de uma arvore
void imprimir_abb(abb *A) {
	if (A != NULL) imprimir_no(A->raiz);
	return;
}
