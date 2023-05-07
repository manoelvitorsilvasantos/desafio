#include "libs.h"
#include "caixa.h"

bool save_venda_caixa(sqlite3 *db, Caixa *caixa){
	int rc=0;
    sqlite3_stmt * stmt;
    const char * tail;
	char *sql = "INSERT INTO caixa(vendedor, descricao, total_venda, dt_venda) VALUES(?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return false;
    }

    rc = sqlite3_bind_text(stmt, 1, caixa->vendedor_nome, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'vendedor': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
    
	rc = sqlite3_bind_text(stmt, 2, caixa->descricao, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'vendedor': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    char price[20];
    sprintf(price, "%.2f", caixa->lucro);
    rc = sqlite3_bind_text(stmt, 3, price, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'preco': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
	
	rc = sqlite3_bind_text(stmt, 4, caixa->datetime, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'Data Venda': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
    
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        fprintf(stderr, "Erro ao executar declaração: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

void lista_vendas(sqlite3 *db){
	sqlite3_stmt *stmt;
    int rc;
    // Prepara a query para selecionar todos os produtos
    const char *query = "SELECT vendedor, descricao, total_venda, dt_venda FROM caixa;";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a query: %s\n", sqlite3_errmsg(db));
        return;
    }
    // Executa a query e lista os produtos
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Caixa cx;
		strcpy(cx.vendedor_nome, ((const char*)sqlite3_column_text(stmt, 0)));
		strcpy(cx.descricao, ((const char*)sqlite3_column_text(stmt, 1)));
		cx.lucro = (float) atof((const char*) sqlite3_column_text(stmt, 2));
		strcpy(cx.datetime, ((const char*)sqlite3_column_text(stmt, 3)));
		
        printf("Vendedor:%s\n", cx.vendedor_nome);
        printf("Tipo de Pagamento:%s\n", cx.descricao);
        printf("Total: R%c%.2f\n", CIFRAO, cx.lucro);
        printf("Data da Venda: %s\n", cx.datetime);
        printf("====================================\n");
    }

    // Verifica se ocorreu algum erro ao executar a query
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro ao executar a query: %s\n", sqlite3_errmsg(db));
    }

    // Libera a memória usada pelo statement
    sqlite3_finalize(stmt);
    fflush(stdin);
}

