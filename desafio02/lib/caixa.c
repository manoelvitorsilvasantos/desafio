#include "libs.h"
#include "caixa.h"

int save_venda_caixa(sqlite3 * db, Caixa *caixa){
	char *err_msg = 0;
	int rc=0;
	char sql[100];
	sprintf(sql, "INSERT INTO caixa(descricao, lucro, ) VALUES('%s', '%f', '%d')", produto->nome, produto->preco, produto->qtd);
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Erro SQL: %s\n", err_msg);
		sqlite3_free(err_msg);
		return 1;
	}
	fflush(stdin);
	free(err_msg);
	return 0;
}
