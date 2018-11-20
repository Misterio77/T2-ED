#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

struct _supp {
	int num;
	int cont;
	ABB *tree;
	struct _supp next;
}

struct _list {
	SUPP *supp;
	int item;
}

struct _prod {
	int item;
	struct _prod *next;
}

struct _shop {
	int num_item;
	PROD next;
}



LIST *create_list () {
	LIST *l;
	l = (LIST*) malloc(sizeof(LIST));
	if(l != NULL){
		l->supp = NULL;
		return(l);
	}
	return(NULL);
}

SUPP create_supplier () {
	SUPP *s;
	s = (SUPP*) malloc(sizeof(SUPP));
	if(s != NULL) return(s);
	return(NULL);
}

SHOP *create_shop () {
	SHOP *s;
	s = (SHOP*) malloc(sizeof(SHOP));
	s->num_item = 0;
	s->next = NULL;
	if(s != NULL)return(s);
	return(NULL);
}

PROD *create_prod () {
	PROD *p;
	p = (PROD*) malloc(sizeof(PROD));
	p->item = 0;
	p->next = NULL;
	if(p != NULL)return(p);
	return(NULL);
}

void insert_item(SHOP shop, int item) {
	if(shop != NULL){
		PROD *aux = create_prod();
		aux->item = item;
		aux->next = shop->next;
		shop->next = aux;
	}
	return;
}

void insert_list(LIST list, SUPP *supp){
	if(supp != NULL){
		supp->next = list->supp;
		list->supp = supp;
	}
	return;
}

LIST *read_file_sup(char *file) {

	FILE *file_in = fopen(file, "r"); //Abrir arquivo
	SUPP supp;
	int n, m, item;
	LIST *l = create_list();
	fscanf(file_in, "%d", &n);
	l->item = n;
	for(int i = 0; i < n; i++){
		supp = create_supplier();
		supp->tree = criar_arvore();
		fscanf(file_in, "%d", &supp->num);
		fscanf(file_in, "%d", &m);
		supp->cont = 0;
		for(int j = 0; j < m; j++){
			fscanf(file_in, "%d", &item);
			inserir_abb(supp->tree, item);
		}
		insert_list(l, supp);
	}
	return(l);
}

SHOP *read_file_shop(char *file) {
	int n, item;
	SHOP *shop = create_shop();
	FILE *file_in = fopen(file, "r"); //Abrir arquivo
	fscanf(file_in, "%d", &n);
	shop->num_item = n;
	for(int i = 0; i < n; i++){
		fscanf(file_in, "%d", &item);
		insert_item(shop, item);
	}
	return(shop);
}

SUPP *search_supp(LIST *list, int num){
	if(list != NULL){
		SUPP *aux = list->supp;
		while(aux->num != num && aux != NULL)aux = aux->next;
		return(aux);
	}
	return(NULL);
}

void remove_item(SHOP shop, int item){
	if(shop != NULL){
		PROD *aux1, *aux2;
		aux1 = shop->next;
		aux2 = shop->next;
		while(aux1->item != item && aux1 != NULL) {
			aux2 = aux1
			aux1 = aux1->next;
		}
		if(aux1 != aux2){ //se nao for o primeiro item
			aux2->next = aux1->next;
			free(aux1);
		}else {
			shop = shop->next;
			free(aux1);
		}
	}
	return;
}

void set_zero(LIST *list) { //muda todos cont diferentes de -1 para zero;
	SUPP *aux;
	aux = list->next;
	while(list->next != NULL)
		if(list->cont != (-1))
			list->cont = 0;
	return;
}

void max_inter(LIST list, int *arr, int n){
	int cont = 0;
	SUPP *s; 	//armazena um fornecedor variavel
	SUPP *max;	//armazena o fornecedor com a maior interseccao
	s = list->next;
	for(int i = 0; i < n; i++){		//arr contem todos itens da loja
		if(arr[i] != 0){			//se o valor do item for zero, ja possui um fornecedor estabelecido
			while(s->next != NULL){
				if(s->cont != (-1))	//se o contador do fornecedor for negativo, ja foi utilizado
					if(busca_abb(s->tree, arr[i]))//verifica se o fornecedor possui o item
						s->cont++;
				s = s->next;
			}
		}
	}
	s = list->next;
	while(s->next != NULL){	//percorre todos fornecedores nao utilizados
		if(s->cont != (-1))
			if(s->cont > cont)
				max = s;	// guarda ponteiro para fornecedor com maior interseccao
		s = s->next;
	}
	max->cont = -1;			//marcador negativo para simbolizar que ja foi utilizado
	for(int i = 0; i < n; i++)
		if(busca_abb(max->tree, arr[i]))
			arr[i] = 0;		//muda os valores dos itens da interseccao para zero
	set_zero(list);			//muda todos marcadores nao negativos para zero
	max_inter(list, arr, n);
}

SHOP *min_supplier(LIST *list, SHOP *shop){
	int *aux;
	PROD *p;
	p = shop->next;
	aux = (int*) malloc((shop->num_item)*sizeof(int));
	for(int i = 0; p->next != NULL; i++){
		aux[i] = p->item;
		p = p->next;
	}
	max_inter(list, aux);
	SHOP *min_sup;
	min_sup = create_shop();
	p = shop->next;
	for(int i = 0; p->next != NULL; i++){
		if(p->cont == -1){
			insert_item(min_sup, p->item);
		}
	}
	return(min_sup);
}
