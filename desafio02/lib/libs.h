#ifndef _LIBS_H_
#define _LIBS_H_
#define CIFRAO 36
#define PORCENTAGEM 37
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
#include <openssl/md5.h>
#define MAX_HASH_LEN 64
#ifdef __cplusplus
extern "C"{
#endif
//estruturas de dados uteis.



char vendedor[30];

typedef struct{
	char vendedor_nome[30];
	char descricao[200];
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


typedef struct{
	char nome[40];
	char pix[100];
	char qrcode[32];
	char banco_codigo[4];
}Empresa;

int sizeProduto(Produto produto);
int sizeItem(Item item);
int sizeCaixa(Caixa caixa);
int sizeUsuario(Usuario usuario);
double percDesconto(float preco_desconto, float preco_original);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
