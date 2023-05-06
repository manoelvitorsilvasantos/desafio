#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <conio.h> // para getch()
#include <time.h>

typedef struct{
	char vendedor[30];
	char descricao[30];
	float valor;
	char data[16];
}Caixa;

typedef struct{
	char nome[30];
	int idade;
}Aluno;

void test();
bool openDatabase();
bool setInfoCaixa(Caixa *caixa);
void testLista(int TAM, int vetor[TAM]);

int main(){
	bool status = openDatabase();
	if(status!=true){
		printf("Erro ao abrir banco de dados.\n");
	}
	else{
		printf("[DATABASE OK]\n");
	}

	
	/*
	strcpy(aluno[0].nome, "manoel");
	strcpy(aluno[1].nome, "vitor");
	aluno[0].idade = 21;
	aluno[1].idade = 32;
	int tam = sizeof(aluno)/sizeof(Aluno);
	printf("Tamanho do vetor: %d\n", tam);
	*/
	/*
	
	Caixa * caixa;
	strcpy(caixa->vendedor, "victor");
	strcpy(caixa->descricao, "Normal");
	caixa->valor = 2.50;
	strcpy(caixa->data, "");
	status=false;
	status = setInfoCaixa(caixa);
	if(status!=false){
		printf("Salvo com sucesso!\n");
	}*/
	
	int TAM = 5;
	int *vetor = (int*)malloc(sizeof(int)*TAM);
	
	testLista(TAM, vetor);
	
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
		caixa->vendedor, caixa->descricao, caixa->valor, datetime
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



