#include "pagamento.h"
#include "principal.h"
#include "caixa.c"
#include "pix.c"

#define TAG_PIX "PIX"
#define TAG_DINHEIRO "DINHEIRO"
#define TAG_CC "CARTÃO DE CRÉDITO"
#define TAG_CD "CARTÃO DE DÉBITO"

void menu_pagamento_forma(int TAM, sqlite3* db, float total, float desconto, char vendedor[30], Produto vetor[TAM]){
	int opcoes;
	opcoes=-1;
	char qrcode[32];
	bool efetuado;
	efetuado=false;
	while(1){
		fflush(stdin);
		system("cls");
		printf("[1] - PIX\n");
		printf("[2] - DINHEIRO\n");
		printf("[3] - Cartão de Crédito\n");
		printf("[4] - Cartão de Débito\n");
		scanf("%d", &opcoes);
		fflush(stdin);
		switch(opcoes){
			case 1:{
				while(1){
					fflush(stdin);
					system("cls");
					printf("======================================\n");
					listar();
					printf("======================================\n");
					printf("Vendedor: %s\n", vendedor);
					printf("Pagamento R%c %.2f Aguardando Pagamento...!\n", CIFRAO,total);
					printf("Digite o qrcode >> ");
					scanf("%32s", qrcode);
					fflush(stdin);
					//verificarPagamento(db, ponteiro_qrcode,&empresa);
					
					if(strcmp(qrcode, QRCODE_NUBANK)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else if(strcmp(qrcode, QRCODE_PICPAY)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else if(strcmp(qrcode, QRCODE_BRADESCO)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else if(strcmp(qrcode, QRCODE_SANTADER)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else if(strcmp(qrcode, QRCODE_BB)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else if(strcmp(qrcode, QRCODE_ITAU)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else if(strcmp(qrcode, QRCODE_CAIXA)==0){
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
					}
					else{
						printf(" Ainda não recebemos o pagamento!\n");
						continue;
					}	
				}
				break;
			}
			case 2:{
				notaFiscal(TAM, db, total, desconto, vendedor, vetor, 1);
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				printf("======================================\n");
				char c;
				c = getchar();
				menu_caixa(db);
				break;
			}
			case 3:{
				int senha;
				senha=0;
				while(1)
				{
					printf("Digite a senha do Cartão: ");
					scanf("%d", &senha);
					if(senha!=2161){
						printf("Senha incorreta!\n");
						continue;
					}
					else{
						break;
					}
				};
				notaFiscal(TAM, db, total, desconto, vendedor, vetor, 2);
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				printf("======================================\n");
				char c;
				c = getchar();
				menu_caixa(db);
				break;
			}
			case 4:{
				int senha;
				senha=0;
				while(1)
				{
					printf("Digite a senha do Cartão: ");
					scanf("%d", &senha);
					if(senha!=2161){
						printf("Senha incorreta!\n");
						continue;
					}
					else{
						break;
					}
				};
				notaFiscal(TAM, db, total, desconto, vendedor, vetor, 3);
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				printf("======================================\n");
				char c;
				c = getchar();
				menu_caixa(db);
				break;
			}
			default:{
				system("cls");
				printf("======================================\n");
				printf("Opção Inválida!\n");
				printf("Selecione uma forma de Pagamento!\n");
				printf("======================================\n");
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				printf("======================================\n");
				char c;
				c = getchar();
			}
		}
		
	}
	
}

void notaFiscal(int TAM, sqlite3* db,float total, float desconto, char vendedor[30], Produto produto[TAM], int forma_pagamento){
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char datetime[20];
	strftime(datetime, sizeof(datetime), "%d/%m/%Y %H:%M:%S", tm);
	int i;
	bool rs;
	i=0;
	rs=false;
	switch(forma_pagamento){
		case 0:{ //pix.
			system("cls");
			printf("======================================\n");
			printf("|| Pagamento Via PIX\n");
			printf("|| Vendedor: %s\n", vendedor);
			printf("|| Data da Compra: %s\n", datetime);
			printf("|| Total: R%c %.2f\n",CIFRAO, total);
			printf("|| Desconto: %.2lf%%\n", percDesconto(desconto, total));
			printf("|| Total à Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| Código: %d\n", produto[i].codigo);
				printf("|| Descrição: %s\n", produto[i].nome);
				printf("|| Preço:R%c %.2f\n", CIFRAO, produto[i].preco);
				printf("|| Qtd: %d\n", produto[i].qtd);
				printf("======================================\n");
			}
			fflush(stdin);
			Caixa cf;
			strcpy(cf.vendedor_nome, vendedor);
			strcpy(cf.descricao, TAG_PIX);
			cf.lucro = total;
			strcpy(cf.datetime, datetime);
			rs=save_venda_caixa(db,&cf);
			if(rs!=true){
				printf("[ERROR]\n");
			}
			printf("======================================\n");
			printf("|| Obrigado pela Preferência!\n");
			printf("======================================\n");
			
			break;
		}
		case 1:{ //DINHEIRO.
			system("cls");
			printf("======================================\n");
			printf("|| Pagamento Via DINHEIRO\n");
			printf("|| Vendedor: %s\n", vendedor);
			printf("|| Data da Compra: %s\n", datetime);
			printf("|| Total: R%c %.2f\n",CIFRAO, total);
			printf("|| Desconto: %.2lf%%\n", percDesconto(desconto, total));
			printf("|| Total à Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| Código: %d\n", produto[i].codigo);
				printf("|| Descrição: %s\n", produto[i].nome);
				printf("|| Preço:R%c %.2f\n", CIFRAO, produto[i].preco);
				printf("|| Qtd: %d\n", produto[i].qtd);
				printf("======================================\n");
			}
			fflush(stdin);
			Caixa cf;
			strcpy(cf.vendedor_nome, vendedor);
			strcpy(cf.descricao, TAG_DINHEIRO);
			cf.lucro = total;
			strcpy(cf.datetime, datetime);
			rs=save_venda_caixa(db,&cf);
			if(rs!=true){
				printf("[ERROR]\n");
			}
			printf("======================================\n");
			printf("|| Obrigado pela Preferência!\n");
			printf("======================================\n");
			
			break;
		}
		case 2:{ //CC
			system("cls");
			printf("======================================\n");
			printf("|| Pagamento Via CC\n");
			printf("|| Vendedor: %s\n", vendedor);
			printf("|| Data da Compra: %s\n", datetime);
			printf("|| Total: R%c %.2f\n",CIFRAO, total);
			printf("|| Desconto: %.2lf%%\n", percDesconto(desconto, total));
			printf("|| Total à Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| Código: %d\n", produto[i].codigo);
				printf("|| Descrição: %s\n", produto[i].nome);
				printf("|| Preço:R%c %.2f\n", CIFRAO, produto[i].preco);
				printf("|| Qtd: %d\n", produto[i].qtd);
				printf("======================================\n");
			}
			fflush(stdin);
			Caixa cf;
			strcpy(cf.vendedor_nome, vendedor);
			strcpy(cf.descricao, TAG_CC);
			cf.lucro = total;
			strcpy(cf.datetime, datetime);
			rs=save_venda_caixa(db,&cf);
			if(rs!=true){
				printf("[ERROR]\n");
			}
			printf("======================================\n");
			printf("|| Obrigado pela Preferência!\n");
			printf("======================================\n");
			
			break;
		}
		case 3:{ //CC
			system("cls");
			printf("======================================\n");
			printf("|| Pagamento Via Cartão de Débito\n");
			printf("|| Vendedor: %s\n", vendedor);
			printf("|| Data da Compra: %s\n", datetime);
			printf("|| Total: R%c %.2f\n",CIFRAO, total);
			printf("|| Desconto: %.2lf%%\n", percDesconto(desconto, total));
			printf("|| Total à Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| Código: %d\n", produto[i].codigo);
				printf("|| Descrição: %s\n", produto[i].nome);
				printf("|| Preço:R%c %.2f\n", CIFRAO, produto[i].preco);
				printf("|| Qtd: %d\n", produto[i].qtd);
				printf("======================================\n");
			}
			fflush(stdin);
			Caixa cf;
			strcpy(cf.vendedor_nome, vendedor);
			strcpy(cf.descricao, TAG_CD);
			cf.lucro = total;
			strcpy(cf.datetime, datetime);
			rs=save_venda_caixa(db,&cf);
			if(rs!=true){
				printf("[ERROR]\n");
			}
			printf("======================================\n");
			printf("|| Obrigado pela Preferência!\n");
			printf("======================================\n");
			
			break;
		}
	}
}

void listar(){
	printf("%s: %s\n",TAG_NUBANK, QRCODE_NUBANK);
	printf("%s: %s\n",TAG_PICPAY, QRCODE_PICPAY);
	printf("%s: %s\n",TAG_BRADESCO, QRCODE_BRADESCO);
	printf("%s: %s\n",TAG_SANTADER, QRCODE_SANTADER);
	printf("%s: %s\n",TAG_BB, QRCODE_BB);
	printf("%s: %s\n",TAG_ITAU, QRCODE_ITAU);
	printf("%s: %s\n",TAG_CAIXA, QRCODE_CAIXA);
}

void verificarPagamento(sqlite3* db, char *qrcode, Empresa *empresa){
	sqlite3_stmt *stmt;
    char sql[1000];
    int rc;
    sprintf(sql, "SELECT pix, qrcode, banco_codigo FROM empresa WHERE qrcode = '%s' LIMIT 1", qrcode);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta SQL: %s\n", sqlite3_errmsg(db));
    }
    else{
		rc = sqlite3_step(stmt);
    	if (rc == SQLITE_ROW){
    		strcpy(empresa->pix,"Comércio Leve LTDA");
    		strcpy(empresa->pix,((const char*)sqlite3_column_text(stmt,0)));
    		strcpy(empresa->qrcode,((const char*)sqlite3_column_text(stmt,1)));
    		strcpy(empresa->banco_codigo,((const char*)sqlite3_column_text(stmt,2)));
    	}else{
        	printf("QRCODE Errado.\n");
        	char c;
			c = getchar();
 	    }	
	}
    sqlite3_finalize(stmt);		
}





