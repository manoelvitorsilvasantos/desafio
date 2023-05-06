
1. Open Dev Cpp++ 

2. Tools > Compiler Options.. > Add the folling commands when calling the linker:

3. Copy and cole: -lsqlite3


Source Code Example.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main(void){
	sqlite3 * db;
	char* err_msg=0;
	char nome_banco[23];
	int rc;
	
	printf("Nome do banco de dados >> \n");
	fflush(stdin);
	fgets(nome_banco,20,stdin);
	
	//nome do banco de dados.
	strcat(nome_banco, ".db");
	
	rc = sqlite3_open(nome_banco, &db);
	
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Não é possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	
	char* sql = "CREATE TABLE IF NOT EXISTS Produtos("
				"id INTEGER PRIMARY KEY AUTOINCREMENT,"
				"nome TEXT NOT NULL,"
				"preco REAL NOT NULL);";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	
	if(rc!=SQLITE_OK){
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		sqlite3_free(err_msg);
		sqlite3_close(db);
		return 1;
	}
	
	sqlite3_close(db);
	return 0;
}