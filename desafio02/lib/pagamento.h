#ifndef _PAGAMENTO_H_
#define _PAGAMENTO_H_
#include "libs.h"
#include "banco.h"
#ifdef __cplusplus
extern "C"{
#endif
//outras funcoes.
bool verificarPagamento(char *qrcode);
void listar(sqlite3 *db);
void notaFiscal(int TAM, sqlite3* db,float total, float desconto, char vendedor[30], Produto produto[TAM], int forma_pagamento);
void menu_pagamento_forma(int TAM, sqlite3* db, float total, float desconto, char vendedor[30], Produto vetor[TAM]);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
