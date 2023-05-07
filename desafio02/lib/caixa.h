#ifndef _CAIXA_H_
#define _CAIXA_H_
#include "libs.h"
#ifdef __cplusplus
extern "C"{
#endif
bool save_venda_caixa(sqlite3 * db, Caixa *caixa);
void lista_vendas(sqlite3 *db);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
