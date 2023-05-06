#include "produto.h"

//pegar informações do produto para salvar.
Produto registrar_produto(){
	setlocale(LC_ALL, "Portuguese");
	Produto produto;
	fflush(stdin);
    printf("Produto nome: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    fflush(stdin);
    printf("Produto preço: ");
    scanf("%f", &produto.preco);
    fflush(stdin);
    printf("Produto qtd: ");
    scanf("%d", &produto.qtd);
    fflush(stdin);
    return produto;
}

//cadastrar produto.
int cadastrar_produto(sqlite3 * db, Produto * produto){
	char *err_msg = 0;
	int rc=0;
	char sql[100];
	sprintf(sql, "INSERT INTO produtos(nome, preco, qtd) VALUES('%s', '%f', '%d')", produto->nome, produto->preco, produto->qtd);
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

//buscar produto.
int buscar_produto_by_nome(char *nome_produto, sqlite3 *db, Produto *produto) {
    sqlite3_stmt *stmt;
    char sql[1000];
    int rc;
    sprintf(sql, "SELECT nome, preco, qtd FROM Produtos WHERE nome = '%s' LIMIT 1", nome_produto);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta SQL: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
    	produto->codigo = sqlite3_column_int(stmt, 0);
    	strcpy(produto->nome, ((const char*)sqlite3_column_text(stmt, 1)));
        produto->preco = ((float) atof((const char*) sqlite3_column_text(stmt, 2)));
        produto->qtd = sqlite3_column_int(stmt, 3);
    } else {
        printf("Produto não encontrado.\n");
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

//listar produtos.
void listar_produtos(sqlite3 *db) {
    sqlite3_stmt *stmt;
    int rc=0;
    // Prepara a query para selecionar todos os produtos
    const char *query = "SELECT * FROM produtos;";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a query: %s\n", sqlite3_errmsg(db));
        return;
    }
    // Executa a query e lista os produtos
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Produto p;
        p.codigo= (int)atoi((const char*)sqlite3_column_text(stmt, 0));
        strcpy(p.nome, ((const char*)sqlite3_column_text(stmt, 1)));
        p.preco = (float) atof((const char*) sqlite3_column_text(stmt, 2));
        p.qtd = (int) atoi((const char*)sqlite3_column_text(stmt, 3));

        printf("Código:%d\n", p.codigo);
        printf("Nome:%s", p.nome);
        printf("Preço:%.2f\n", p.preco);
        printf("Qtd Estoque:%d\n", p.qtd);
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

//remover produto.
int remover_produto(sqlite3 *db, int codigo) {
    int rc=0;
    char* err_msg=0;
	char sql[100];
	sprintf(sql, "DELETE FROM produtos WHERE codigo=%d", codigo);
	rc = sqlite3_exec(db, sql, 0, 0,&err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Erro ao deletar registro: %s\n", err_msg);
		sqlite3_free(err_msg);
	}
	else{
		printf("Registro deletado com sucesso.\n");
	}
	fflush(stdin);
    return 0;
}

int buscar_produto_by_codigo(sqlite3 * db, int codigo, Produto * produto){
	sqlite3_stmt *stmt;
    char sql[1000];
    int rc;
    sprintf(sql, "SELECT * FROM produtos WHERE codigo = %d", codigo);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta SQL: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
    	produto->codigo = (int)atoi((const char*) sqlite3_column_text(stmt, 0));
        strcpy(produto->nome, ((const char*)sqlite3_column_text(stmt, 1)));
        produto->preco = (float) atof((const char*) sqlite3_column_text(stmt, 2));
        produto->qtd = (int)atoi((const char*) sqlite3_column_text(stmt, 3));
        return 1;
    } 
    sqlite3_finalize(stmt);
    return 0;
}


int atualizar_produto_preco_by_codigo(sqlite3 * db, int codigo, float preco){
    int rc=0;
    sqlite3_stmt * stmt;
    const char * tail;
    char sql[100];

    sprintf(sql, "UPDATE produtos SET preco = ? WHERE codigo = ?");

    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    
    char price[20];
    sprintf(price, "%.2f", preco);
    rc = sqlite3_bind_text(stmt, 1, price, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'preco': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_bind_int(stmt, 2, codigo);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'codigo': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        fprintf(stderr, "Erro ao executar declaração: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Preço atualizado com sucesso.\n");
    return 1;
}



int atualizar_produto_qtd_by_codigo(sqlite3 * db, int codigo, int qtd){
    int rc=0;
    sqlite3_stmt * stmt;
    const char * tail;
    char sql[100];

    sprintf(sql, "UPDATE produtos SET qtd = qtd + ? WHERE codigo = ?");

    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    
    rc = sqlite3_bind_int(stmt, 1, qtd);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'Qtd': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_bind_int(stmt, 2, codigo);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'codigo': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        fprintf(stderr, "Erro ao executar declaração: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }
    else{
    	printf("Estoque atualizado.\n");
    	sqlite3_finalize(stmt);
    	return 1;
    }
	
	
    sqlite3_finalize(stmt);
    return 0;
}

int atualizar_produto_by_codigo(sqlite3 * db, int codigo, Produto *produto){
    int rc=0;
    sqlite3_stmt * stmt;
    const char * tail;
    char sql[100];

    sprintf(sql, "UPDATE produtos SET nome = ?, preco = ?, qtd = qtd + ? WHERE codigo = ?");

    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    rc = sqlite3_bind_text(stmt, 1, produto->nome, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'nome': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }
	char price[20];
    sprintf(price, "%.2f", produto->preco);
    rc = sqlite3_bind_text(stmt, 2, price, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'preco': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_bind_int(stmt, 3, produto->qtd);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'qtd': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_bind_int(stmt, 4, codigo);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'codigo': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        fprintf(stderr, "Erro ao executar declaração: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Registro atualizado com sucesso.\n");
    return 1;
}


int comprarProduto(sqlite3 * db, int codigo, int qtd){
    int rc=0;
    sqlite3_stmt * stmt;
    const char * tail;
    char sql[100];

    sprintf(sql, "UPDATE produtos SET qtd = qtd - ? WHERE codigo = ?");

    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    
    rc = sqlite3_bind_int(stmt, 1, qtd);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'Qtd': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_bind_int(stmt, 2, codigo);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'codigo': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        fprintf(stderr, "Erro ao executar declaração: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("Estoque atualizado.\n");
    return 1;
}


int produto_existe(sqlite3 * db, int codigo){
	sqlite3_stmt *stmt;
    char sql[1000];
    int rc;
    sprintf(sql, "SELECT * FROM produtos WHERE codigo = '%d'", codigo);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta SQL: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        return 1;
    } 
    sqlite3_finalize(stmt);
    return 0;
}

