#ifndef funcoes_h
#define funcoes_h

#include "estruturas.h"

typedef struct _abb abb;

int arvore_vazia(abb *A);
int busca_abb(ABB *A, int item);
abb *criar_arvore();
void inserir_abb(abb *A, int num);
void remove_item(abb *A, int item);
void remove_arvore(abb *A);

#endif
