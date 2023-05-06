#include "pagamento.h"
#include "principal.h"

void menu_pagamento_forma(int TAM, sqlite3* db, float total, char vendedor[30], Produto vetor[TAM]){
	int opcoes;
	opcoes=-1;
	while(1){
		fflush(stdin);
		system("cls");
		printf("[4] - PIX\n");
		printf("[1] - DINHEIRO\n");
		printf("[2] - Cart�o de Cr�dito\n");
		printf("[3] - Cart�o de D�bito\n");
		scanf("%d", &opcoes);
		fflush(stdin);
		
		switch(opcoes){
			case 0:{
				continue;
				break;
			}
			case 1:{
				printf("======================================\n");
				printf("Vendedor: %s\n", vendedor);
				printf("Pagamento %.2f efetuado com sucesso!\n", total);
				notaFiscal(TAM, total, vendedor, vetor, 0);
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				printf("======================================\n");
				char c;
				c = getchar();
				menu_caixa(db);
				//getNone();
				break;
			}
			case 2:{
				getNone();
				break;
			}
			case 3:{
				getNone();
				break;
			}
			case 4:{
				getNone();
				break;
			}
			default:{
				fflush(stdin);
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

void notaFiscal(int TAM, float total, char vendedor[30], Produto produto[TAM], int forma_pagamento){
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char datetime[20];
	strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm);
	int i;
	i=0;
	switch(forma_pagamento){
		case 0:{ //dinheiro fisico.
			printf("======================================\n");
			printf("|| Pagamento Via PIX\n");
			printf("|| Vendedor: %s\n", vendedor);
			printf("|| Data da Compra: %s\n", datetime);
			printf("======================================\n");
			printf("======================================\n");
			for(i=0;i<TAM;i++){
				printf("|| C�digo: %d\n", produto[i].codigo);
				printf("|| Descri��o: %s\n", produto[i].nome);
				printf("|| Pre�o: %.2f\n", produto[i].preco);
				printf("|| Qtd: %d\n", produto[i].qtd);
				printf("======================================\n");
			}
			printf("======================================\n");
			printf("|| Obrigado pela Prefer�ncia!\n");
			printf("======================================\n");
			break;
		}
	}
	
}

void setPagamento(float valor, int forma_pagamento){
	
}

float getPagamento(){
	return 0.0;
}
