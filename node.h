#ifndef	node_h
#define node_h

typedef struct _no no;

no *criar_no();
no *busca_no(no *raiz, int chave);
no *inserir_no(no *B, int num);
void contar_no_aux(no *raiz, int *cont);
int contar_no(no *raiz);
void altura_no(no *raiz, int *max, int atual);
int estri_binaria_no(no *raiz);
int fator_balanceamento_no(no *raiz);
int balanceado_no(no *raiz);
int perf_balanceado_no(no *raiz);
void remove_c1(no *ant, no *rem);
void remove_c2(no *ant, no *rem);
void remove_c3(no *ant, no *rem);
void remover_no(no *raiz, int chave);
void limpar_no(no *raiz);

#endif
