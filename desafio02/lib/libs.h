#ifndef _LIBS_H_
#define _LIBS_H_
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <float.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#ifdef __cplusplus
extern "C"{
#endif
//estruturas de dados uteis.



char vendedor[30];

typedef struct{
	int codigo;
	char vendedor[30];
	char descricao[30];
	float lucro;
	char datetime[20];
}Caixa;

typedef struct{
	int codigo;
	char usuario[30];
	char senha[30];
	char email[100];
	int state;
}Usuario;

typedef struct Produto{
	int codigo;
	char nome[30];
	float preco;
	int qtd;
}Produto;

typedef struct node{
	Produto produto;
	struct node* next;
}Node;


typedef struct{
	float preco;
	char descricao;
	int codigo;
	int total;
}Item;


int sizeProduto(Produto produto);
int sizeItem(Item item);
int sizeCaixa(Caixa caixa);
int sizeUsuario(Usuario usuario);


#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
