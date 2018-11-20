#include <stdlib.h>
#include <stdio.h>
#include "tree.h"


struct _no {
	int item;
	struct _no *esq, *dir;
};

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

//funcao que busca um no tendo um item como referencia
no *busca_no(no *raiz, int chave) {
	while (raiz != NULL && (raiz->item) != chave) {
		if (chave < (raiz->item)) raiz = raiz->esq;
		else raiz = raiz->dir;
	}
	return(raiz);
}

//funcao que insere um item em um no ainda nao alocado
no *inserir_no(no *B, int num) {

	B = busca_no(B, num);
	if(B == NULL) {
		B = criar_no();
		if(B != NULL) {
			B->item = num;
			return (B);
		}
		return (NULL);
	}
	return (B);
}

//funcao auxiliar de contar nos
void contar_no_aux(no *raiz, int *cont) {
	if (raiz != NULL) {
		(*cont)++;
		contar_no_aux(raiz->esq, cont);
		contar_no_aux(raiz->dir, cont);
	}
	return;
}

//funcao conta quantos filhos do total tem o no
int contar_no(no *raiz) {
	if (raiz != NULL) {
		int *cont;
		cont = (int*) malloc(sizeof(int));
		(*cont) = 0;
		contar_no_aux(raiz, cont);
		return(*cont);
	}
	return (-200);//erro
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

//funcao retorna 0 se o no for estritamente binario e !0 se não for.
int estri_binaria_no(no *raiz) {
	if (raiz != NULL) {
		if((raiz->dir == NULL) ^ (raiz->esq == NULL)){
			return(1);
		}
		else return (estri_binaria_no(raiz->esq) + estri_binaria_no(raiz->dir));
	} 
	return(0);	
}

//funcao retorna o fator de balanceamento do no dado.
int fator_balanceamento_no(no *raiz) {
	if (raiz != NULL) {
		int *altesq, *altdir, aux = 0;
		altesq = (int*) malloc(sizeof(int));
		altdir = (int*) malloc(sizeof(int));
		(*altesq) = 0;
		(*altdir) = 0;
		altura_no(raiz->esq, altesq, aux);
		aux = 0;
		altura_no(raiz->dir, altdir, aux);
		return ((*altesq) - (*altdir));
	}
	return (-200);//erro
}

//funcao retorna 0 se o no estiver balanceado e !0 se nao
int balanceado_no(no *raiz) {
	if (raiz != NULL) {
		if (abs(fator_balanceamento_no(raiz)) < 2) return (balanceado_no(raiz->esq) + balanceado_no(raiz->dir));
		return (1);
	}
	return (0);
}

//funcao retorna 0 se o no for perfeitamente balanceado e !0 se nao.
int perf_balanceado_no(no *raiz) {
	if (raiz != NULL) {
		if(abs(contar_no(raiz->esq) - contar_no(raiz->dir)) < 2) return (perf_balanceado_no(raiz->esq) + perf_balanceado_no(raiz->dir));
		return (1);
	}
	return (0);
}

//remove um no que nao tem filhos
void remove_c1(no *ant, no *rem) {
	if ((ant->item) > (rem->item)) ant->esq = NULL;
	else ant->dir = NULL;
	free(rem);
	return;
}

//remove um no que tem apenas um filho.
void remove_c2(no *ant, no *rem) {
	if (ant->item > rem->item) {
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
		rem->item = aux->item;
		rem->esq = aux->esq;
		free(aux);
		return;
	}
	while(aux->dir != NULL) {
		ant = aux;
		aux = aux->dir;
	}
	rem->item = aux->item;
	ant->dir = aux->esq;
	free(aux);
	return;
}

//remove um no
void remover_no(no *raiz, int chave) {
	no *aux;
	aux = (no*)malloc(sizeof(no));
	if (aux != NULL) {
		while (raiz != NULL && (raiz->item) != chave) {
			aux = raiz;
			if (chave < (raiz->item)) raiz = raiz->esq;
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

//percorre e imprime todos nos de uma arvore
void imprimir_no(no *raiz, int *cont) {
	if (raiz != NULL) {
		(*cont)++;
		contar_no_aux(raiz->esq, cont);
		printf("-%d-", raiz->item);
		contar_no_aux(raiz->dir, cont);
	}
	return;
}
