#ifndef _CAIXA_H_
#define _CAIXA_H_
#include "libs.h"
#ifdef __cplusplus
extern "C"{
#endif
void buy_produto(sqlite3* db);
int save_venda_caixa(sqlite3 * db, Caixa *caixa);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
