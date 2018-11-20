#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

struct _supp { 	//struct de fornecerdor
	int num; 	//codigo do fornecedor
	int cont;	//contador de interseccao
	ABB *tree;	//itens do fornecedor em uma ABB
	struct _supp next;
}

struct _list { //no cabeca da lista de fornecedores
	SUPP *supp;
	int item;
}

struct _prod { //struct de item da loja
	int item;
	struct _prod *next;
}

struct _shop { //no cabeca da lista da loja
	int num_item;
	PROD next;
}



LIST *create_list () { //cria lista vazia de fornecedores
	LIST *l;
	l = (LIST*) malloc(sizeof(LIST));
	if(l != NULL){
		l->supp = NULL;
		return(l);
	}
	return(NULL);
}

SUPP create_supplier () { //cria um fornecedor
	SUPP *s;
	s = (SUPP*) malloc(sizeof(SUPP));
	if(s != NULL) return(s);
	return(NULL);
}

SHOP *create_shop () { //cria uma nova lista vazia de loja
	SHOP *s;
	s = (SHOP*) malloc(sizeof(SHOP));
	s->num_item = 0;
	s->next = NULL;
	if(s != NULL)return(s);
	return(NULL);
}

PROD *create_prod () { //cria um produto para loja
	PROD *p;
	p = (PROD*) malloc(sizeof(PROD));
	p->item = 0;
	p->next = NULL;
	if(p != NULL)return(p);
	return(NULL);
}

void insert_item(SHOP shop, int item) { //insere produto na loja
	if(shop != NULL){
		PROD *aux = create_prod();
		aux->item = item;
		aux->next = shop->next;
		shop->next = aux;
	}
	return;
}

void insert_list(LIST list, SUPP *supp){ //insere fornecedor na lista
	if(supp != NULL){
		supp->next = list->supp;
		list->supp = supp;
	}
	return;
}

LIST *read_file_sup(char *file) { 		//le arquivo de entrada para fornecedores e cria lista

	FILE *file_in = fopen(file, "r"); 	//Abrir arquivo
	SUPP supp;
	int n, m, item;
	LIST *l = create_list(); 			//cria lista de fornecedores
	fscanf(file_in, "%d", &n);
	l->item = n;						//numero atual de fornecedores
	for(int i = 0; i < n; i++){
		supp = create_supplier();		//cria novo fornecedor
		supp->tree = criar_arvore();	//cria arvore de produtos
		fscanf(file_in, "%d", &supp->num);//nome do fornecedor
		fscanf(file_in, "%d", &m);
		supp->cont = 0;
		for(int j = 0; j < m; j++){
			fscanf(file_in, "%d", &item);
			inserir_abb(supp->tree, item);// adiciona itens na arvore do fornecedor
		}
		insert_list(l, supp);			//insere fornecedor na lista
	}
	return(l);
}

SHOP *read_file_shop(char *file) { 		//le arquivo de entrada para loja e guarda itens na lista
	int n, item;
	SHOP *shop = create_shop();			//cria lista da loja
	FILE *file_in = fopen(file, "r"); 	//Abrir arquivo
	fscanf(file_in, "%d", &n);
	shop->num_item = n;					//numero atual de itens na loja
	for(int i = 0; i < n; i++){
		fscanf(file_in, "%d", &item);
		insert_item(shop, item);		//insere item
	}
	return(shop);
}

SUPP *search_supp(LIST *list, int num){//busca um forncedor na lista
	if(list != NULL){
		SUPP *aux = list->supp;
		while(aux->num != num && aux != NULL)aux = aux->next;
		return(aux);
	}
	return(NULL);
}

void remove_item(SHOP shop, int item){ //remove um item da loja
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

void max_inter(LIST list, int *arr, int n){//funcao recursiva para encontrar o menor num de fornecedores com a maior intersec
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

SHOP *min_supplier(LIST *list, SHOP *shop){//funcao para encontrar o menor num de fornecedores que contem todos produtos da loja
	int *aux;
	PROD *p;
	p = shop->next;
	aux = (int*) malloc((shop->num_item)*sizeof(int));	//cria vetor para guardar itens da loja
	for(int i = 0; p->next != NULL; i++){
		aux[i] = p->item;								//passa itens da lista da loja para o vetor
		p = p->next;
	}	
	max_inter(list, aux);								//chama a funcao da intersec
	SHOP *min_sup;
	min_sup = create_shop();							//cria uma outra lista de produtos, porem guarda o nome dos fornecedores
	p = shop->next;
	for(int i = 0; p->next != NULL; i++){
		if(p->cont == -1){
			insert_item(min_sup, p->item);				//adiciona todos fornecedores marcados na lista
		}
	}
	return(min_sup);
}
