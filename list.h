#ifndef list_h
#define list_h

#include "tree.h"

typedef struct _supp SUPP;
typedef struct _list LIST;
typedef struct _prod PROD;
typedef struct _shop SHOP;

LIST *create_list ();
SUPP create_supplier ();
SHOP *create_shop ();
PROD *create_prod ();
void insert_item(SHOP shop, int item);
void insert_item_sup(LIST *list, int cod, int item);
void insert_list(LIST list, SUPP *supp);
LIST *read_file_sup(char *file);
SHOP *read_file_shop(char *file);
SUPP *search_supp(LIST *list, int num);
void remove_item(SHOP shop, int item);
void set_zero(LIST *list);
void max_inter(LIST list, int *arr, int n);
SHOP *min_supplier(LIST *list, SHOP *shop);
void print_shop(SHOP shop);
void print_supplier(LIST list, int num);

#endif

