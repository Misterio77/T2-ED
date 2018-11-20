#ifndef tree_h
#define tree_h

#include "node.h"

typedef struct _abb abb;

int arvore_vazia(abb *A);
int busca_abb(abb *A, int item);
abb *criar_arvore();
void inserir_abb(abb *A, int num);
void remover_item(abb *A, int item);
void remover_arvore(abb *A);
void imprimir_abb(abb *A);

#endif
