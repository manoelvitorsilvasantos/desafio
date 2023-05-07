#include "pagamento.h"
#include "principal.h"
#include "caixa.c"
#include "pix.c"

#define TAG_PIX "PIX"
#define TAG_DINHEIRO "DINHEIRO"
#define TAG_CC "CART�O DE CR�DITO"
#define TAG_CD "CART�O DE D�BITO"

void menu_pagamento_forma(int TAM, sqlite3* db, float total, float desconto, char vendedor[30], Produto vetor[TAM]){
	int opcoes;
	opcoes=-1;
	char qrcode[32];
	bool efetuado;
	efetuado=false;
	mostrarChaves();
	while(1){
		fflush(stdin);
		system("cls");
		printf("[1] - PIX\n");
		printf("[2] - DINHEIRO\n");
		printf("[3] - Cart�o de Cr�dito\n");
		printf("[4] - Cart�o de D�bito\n");
		scanf("%d", &opcoes);
		fflush(stdin);
		switch(opcoes){
			case 1:{
				while(1){
					fflush(stdin);
					printf("======================================\n");
					listar(db);
					printf("======================================\n");
					system("cls");
					printf("Vendedor: %s\n", vendedor);
					printf("Pagamento R%c %.2f Aguardando Pagamento...!\n", CIFRAO,total);
					printf("Digite o qrcode >> ");
					fgets(qrcode,32,stdin);
					fflush(stdin);
					
					if(!verificarPagamento(qrcode)){
						printf(" Ainda n�o recebemos o pagamento!\n");
						continue;
					}
					else{
						notaFiscal(TAM, db, total, desconto, vendedor, vetor, 0);
						printf("Tecle [ENTER] para voltar ao Menu.\n");
						printf("======================================\n");
						char c;
						c = getchar();
						menu_caixa(db);
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
					printf("Digite a senha do Cart�o: ");
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
					printf("Digite a senha do Cart�o: ");
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
				printf("Op��o Inv�lida!\n");
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
			printf("|| Total � Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| C�digo: %d\n", produto[i].codigo);
				printf("|| Descri��o: %s\n", produto[i].nome);
				printf("|| Pre�o:R%c %.2f\n", CIFRAO, produto[i].preco);
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
			printf("|| Obrigado pela Prefer�ncia!\n");
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
			printf("|| Total � Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| C�digo: %d\n", produto[i].codigo);
				printf("|| Descri��o: %s\n", produto[i].nome);
				printf("|| Pre�o:R%c %.2f\n", CIFRAO, produto[i].preco);
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
			printf("|| Obrigado pela Prefer�ncia!\n");
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
			printf("|| Total � Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| C�digo: %d\n", produto[i].codigo);
				printf("|| Descri��o: %s\n", produto[i].nome);
				printf("|| Pre�o:R%c %.2f\n", CIFRAO, produto[i].preco);
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
			printf("|| Obrigado pela Prefer�ncia!\n");
			printf("======================================\n");
			
			break;
		}
		case 3:{ //CC
			system("cls");
			printf("======================================\n");
			printf("|| Pagamento Via Cart�o de D�bito\n");
			printf("|| Vendedor: %s\n", vendedor);
			printf("|| Data da Compra: %s\n", datetime);
			printf("|| Total: R%c %.2f\n",CIFRAO, total);
			printf("|| Desconto: %.2lf%%\n", percDesconto(desconto, total));
			printf("|| Total � Pagar: R%c %.2f\n",CIFRAO, (total - desconto));
			printf("|| Troco:R%c %.2f\n",CIFRAO, (total-(total-desconto)));
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| C�digo: %d\n", produto[i].codigo);
				printf("|| Descri��o: %s\n", produto[i].nome);
				printf("|| Pre�o:R%c %.2f\n", CIFRAO, produto[i].preco);
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
			printf("|| Obrigado pela Prefer�ncia!\n");
			printf("======================================\n");
			
			break;
		}
	}
}

void listar(sqlite3 *db){
	sqlite3_stmt *stmt;
    int rc=0;
    // Prepara a query para selecionar todos os produtos
    const char *query = "SELECT b.nome_banco, b.banco_codigo, e.pix, e.qrcode FROM empresa AS e JOIN bancos AS b ON e.banco_codigo =  b.banco_codigo";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a query: %s\n", sqlite3_errmsg(db));
        return;
    }
    // Executa a query e lista os produtos
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Empresa e;
        strcpy(e.nome,((const char*)sqlite3_column_text(stmt, 1)));
        strcpy(e.banco_codigo, ((const char*)sqlite3_column_text(stmt,2)));
		strcpy(e.pix, ((const char*)sqlite3_column_text(stmt,3)));
        strcpy(e.qrcode, ((const char*)sqlite3_column_text(stmt,4)));
        
		printf("Banco:%s\n",e.nome);
        printf("C�digo:%s", e.banco_codigo);
        printf("Chave Pix:%s\n", e.pix);
        printf("QRCODE:%s\n", e.qrcode);
        printf("====================================\n");
    }
    sqlite3_finalize(stmt);
    fflush(stdin);
}

bool verificarPagamento(const char *qrcode){
	return !strcmp(qrcode, QRCODE_NUBANK)&&
	!strcmp(qrcode,QRCODE_PICPAY)&&
	!strcmp(qrcode,QRCODE_BRADESCO)&&
	!strcmp(qrcode,QRCODE_SANTADER)&&
	!strcmp(qrcode,QRCODE_BB)&&
	!strcmp(qrcode,QRCODE_ITAU)&&
	!strcmp(qrcode,QRCODE_CAIXA);			
}





