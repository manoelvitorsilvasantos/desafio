#ifndef _PRODUTO_H_
#define _PRODUTO_H_
#include "libs.h"
#ifdef __cplusplus
extern "C"{
#endif
//funções pra pegar as informações.
void menu(sqlite3 * db);
void menu_produto(sqlite3 * db);
Produto registrar_produto();


//funções para banco de dados.
int remover_produto(sqlite3 *db, int codigo);
int cadastrar_produto(sqlite3 * db, Produto *produto);
int buscar_produto_by_nome(char *nome_produto, sqlite3 *db, Produto *produto);
int buscar_produto_by_codigo(sqlite3 *db, int codigo, Produto * produto);
int atualizar_produto_by_codigo(sqlite3 * db, int codigo, Produto *produto);
int atualizar_produto_preco_by_codigo(sqlite3 * db, int codigo, float preco);
int atualizar_produto_qtd_by_codigo(sqlite3 * db, int codigo, int qtd);
int comprarProduto(sqlite3 * db, int codigo, int qtd);
void listar_produtos(sqlite3 *db);
int produto_existe(sqlite3 * db, int codigo);

#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif

