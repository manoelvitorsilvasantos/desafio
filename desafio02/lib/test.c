#include "pix.c"

typedef struct{
	char nome[30];
	int idade;
}Aluno;

void test();
bool openDatabase();
bool setInfoCaixa(Caixa *caixa);
void testLista(int TAM, int vetor[TAM]);
void listar(sqlite3 *db);
int verificarPagamento(char* qrcode, sqlite3 *db, Empresa *empresa);

int main(){
	sqlite3* db;
	int rc;
	rc=0;
	rc=sqlite3_open("database.db", &db);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Erro ao abrir banco de dados:%s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}

	printf("\n\n");
	mostrarChaves();
	bool rs;
	int bank;
	bank=0;
	rs=false;
	fflush(stdin);
	char qrcode[32];
	while(1){
		Empresa empresa;
		printf("Digite o qrcode >>");
		fgets(qrcode,32,stdin);
		fflush(stdin);
		if(!verificarPagamento(qrcode,db,&empresa)){
			printf("ERROR\n");
			continue;
		}
		else{
			printf("[OK]\n");
		}
	}
	
	char c;
	c = getchar();
	sqlite3_close(db);
	
	return 0;
}


void testLista(int TAM, int vetor[]){
	int i;
	srand(time(NULL));
	i=0;
	for(i=0;i<TAM;i++){
		int valor;
		valor = rand()%10;
		vetor[i] = valor;
		printf("VALOR = %d\n", vetor[i]);
	}
	
}

bool setInfoCaixa(Caixa * caixa){
	sqlite3* db;
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char datetime[20];
	strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm);
	char *err_msg = 0;
	int rc=0;
	char sql[100];
	rc=sqlite3_open("database.db", &db);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Erro ao abrir banco de dados:%s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}
	sprintf(
		sql, 
		"INSERT INTO caixa(vendedor, descricao, valor, data) VALUES('%s', '%s', '%f', '%s')", 
		caixa->vendedor_nome, caixa->descricao, caixa->lucro, datetime
	);
	
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Erro SQL: %s\n", err_msg);
		sqlite3_free(err_msg);
		return true;
	}
	fflush(stdin);
	free(err_msg);
	sqlite3_close(db);
	return false;
}


bool openDatabase(){
	sqlite3* db;
	int rc;
	rc=0;
	rc=sqlite3_open("database.db", &db);
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Erro ao abrir banco de dados:%s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}
	sqlite3_close(db);
	return true;
}


void listar(sqlite3 *db){
	sqlite3_stmt *stmt;
    int rc=0;
    char nome[30];
    // Prepara a query para selecionar todos os produtos
    const char *query = "SELECT b.nome_banco, b.banco_codigo, e.pix, e.qrcode FROM empresa AS e JOIN bancos AS b ON e.banco_codigo =  b.banco_codigo;";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a query: %s\n", sqlite3_errmsg(db));
        return;
    }
    // Executa a query e lista os produtos
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Empresa e;
        strcpy(nome, ((const char*)sqlite3_column_text(stmt, 0)));
        strcpy(e.banco_codigo, ((const char*)sqlite3_column_text(stmt, 1)));
		strcpy(e.pix, ((const char*)sqlite3_column_text(stmt, 2)));
        strcpy(e.qrcode, ((const char*)sqlite3_column_text(stmt, 3)));
		
        printf("Banco:%s\n", nome);
        printf("Código:%s", e.banco_codigo);
        printf("Chave Pix:%s\n", e.pix);
        printf("QRCODE:%s\n", e.qrcode);
        printf("====================================\n");
    }
    fflush(stdin);
}

int verificarPagamento(char* qrcode, sqlite3 *db, Empresa *empresa) {
    sqlite3_stmt *stmt;
    char sql[1000];
    int rc;
    sprintf(sql, "SELECT * FROM empresa WHERE codigo = '%s';", qrcode);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta SQL: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
    	strcpy(empresa->pix,((const char*)sqlite3_column_text(stmt, 0)));
    	strcpy(empresa->qrcode,((const char*)sqlite3_column_text(stmt, 1)));
    	strcpy(empresa->banco_codigo,((const char*)sqlite3_column_text(stmt,2)));
        return 1;
    } 
    sqlite3_finalize(stmt);
    return 0;
}




