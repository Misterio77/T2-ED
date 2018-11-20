#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
	int item, aux, i = 1;
	char *arquivo; //Nome do arquivo
	arquivo = (char*) malloc(sizeof(char)*50);
	
	while (i > 0) {
		printf("\nProblema da Cobertura de Conjuntos");
		printf("\ndigite a funcao desejada(0-10)\n");
		printf("1) Ler arquivo de entrada para loja\n");
		printf("2) Ler arquivo de entrada para fornecedores\n");
		printf("3) Adicionar novo item a loja\n");
		printf("4) Adicionar novo item a um fornecedor\n");
		printf("5) Remover um item da loja\n");
		printf("6) Remover um item de um fornecedor\n");
		printf("7) Imprimir itens da loja\n");
		printf("8) Imprimir itens de um fornecedor\n");
		printf("9) Buscar conjunto minimo de fornecedores\n");
		printf("\n 0)sair \n>");
		scanf("%d", &i);
		
		switch (i) {
			case 1:	printf("Digite o nome do arquivo a ser lido(loja)\n>");
					scanf("%s", arquivo);
					SHOP *s;
					s = read_file_shop(arquivo);
					
					break;
					
			case 2: printf("Digite o nome do arquivo a ser lido(fornecedores)\n>");
					scanf("%s", arquivo);
					LIST *l;
					l = read_file_sup(arquivo);
					
					break;
					
			case 3: printf("Digite o numero do item que deseja inserir na loja\n>");
					scanf("%d", &item);
					insert_item(s, item);
					
					break;
					
			case 4: printf("Digite o numero do fornecedor\n>");
					scanf("%d", &aux);
					printf("Digite o numero do item que deseja inserir no fornecedor\n>");
					scanf("%d", &item);
					insert_item_sup(l, aux, item);
					
					break;
					
			case 5: printf("Digite o numero do item que deseja remover da loja\n>");
					scanf("%d", &item);
					remove_item(s, item);
					
					break;
					
			case 6: printf("Digite o numero do fornecedor\n>");
					scanf("%d", &aux);
					printf("Digite o numero do item que deseja remover do fornecedor\n>");
					scanf("%d", &item);
					remove_item_sup(l, aux, item);
					
					break;
					
			case 7: printf("\nItens da loja:\n");
					print_shop(s);
			
					break;
					
			case 8: printf("Digite o numero do fornecedor\n>");
					scanf("%d", &aux);
					print_supplier(l, aux);
					
					break;
					
			case 9: ;
					SHOP *min_sup;
					min_sup = min_supplier(l, s);
					printf("\nconjunto minimo de fornecedores:\n");
					print_shop(min_sup);
					
					break;	
		}
	}
	return (0);
}

