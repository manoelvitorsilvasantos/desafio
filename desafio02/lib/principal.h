#ifndef _PRINCIPAL_H_
#define _PRINCIPAL_H_
#include "libs.h"
#ifdef __cplusplus
extern "C"{
#endif
//prototipos de funções e procedimentos.
void getNone();
void menu(sqlite3 *db);
void menu_test();
void menu(sqlite3 * db);
void menu_produto(sqlite3 * db);
void menu_cliente(sqlite3 * db);
void menu_vendas(sqlite3 *db);
int authenticate_user(const char *username, const char *password);
void menu_caixa(sqlite3 *db);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif

