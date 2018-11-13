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
void inserir_abb(abb *A, item prod) {
	if (A != NULL) {
		if (arvore_vazia(A)) {
			A->raiz = criar_no();
			inserir_item(A->raiz, prod);
		}
		else inserir_no(A->raiz, prod);
	}
	return;
}

abb *ler_arquivo(char *arquivo) {

	FILE *arqin = fopen(arquivo, "r"); //Abrir arquivo
	
	
	int n; //Ler número de itens
	fscanf(arqin, "%d", &n);
	
	//work in progress
	
	return();
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
	
