#ifndef listas_h
#define listas_h

#include "funcoes.h"

typedef struct _supp supp;
typedef struct _list LIST;
typedef struct _prod prod;
typedef struct _shop shop;

LIST *create_list ();
SUPP create_supplier ();
SHOP *create_shop ();
PROD *create_prod ();
void insert_item(SHOP shop, int item);
void insert_list(LIST list, SUPP *supp);
LIST *read_file_sup(char *file);
SHOP *read_file_shop(char *file);
SUPP *search_supp(LIST *list, int num);
void remove_item(SHOP shop, int item);
void set_zero(LIST *list);
void max_inter(LIST list, int *arr, int n);
SHOP *min_supplier(LIST *list, SHOP *shop);

#endif

