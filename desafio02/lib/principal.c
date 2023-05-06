#include "libs.h"
#include "principal.h"
#include "produto.c"
#include "shop.c"
#include "pagamento.c"

//menu principal.
void menu(sqlite3* db){
	int opcao=-1;
	while(1){
		system("cls");
		printf("======================================\n");
		printf(" PAINEL DE CONTROLE\n");
		printf(" Vendor: %s\n", vendedor);
		printf("======================================\n");
		printf("[1] Clientes\n");
		printf("[2] Produtos\n");
		printf("[3] Caixa\n");
		printf("[4] Test\n");
		printf("[0] Fechar\n");
		printf("======================================\n");
		printf("[x] Digite a opção do Menu >>");
		scanf("%d",&opcao);
		fflush(stdin);
		system("cls");
		switch(opcao){
			case 0:{
				printf("======================================\n");
				printf(" APLICATIVO FECHADO\n");
				printf("======================================\n");
				exit(0);
				break;
			}
			case 1:{
				menu_cliente(db);
				break;
			}
			case 2:{
				menu_produto(db);
				break;
			}
			case 3:{
				menu_caixa(db);
				break;
			}
			case 4:{
				getNone();
				break;
			}
			default:{
				fflush(stdin);
				printf("======================================\n");
				printf("Opção Inválida!\n");
				printf("======================================\n");
				char c;
				c = getchar();
			}
		}
	}
}


//menu produto.
void menu_produto(sqlite3* db){
	setlocale(LC_ALL, "Portuguese");
	int opcoes=-1;
	int rc=0;
	int rc_2=0;
	int codigo=0;
	int qtd;
	qtd=0;
	float preco;
	preco=0.0;
	while(1){
		system("cls");
		printf("======================================\n");
		printf(" CONTROLE DE ESTOQUE\n");
		printf(" Vendor: %s\n", vendedor);
		printf("======================================\n");
		printf("[1] Cadastrar Novo Produto\n");
		printf("[2] Remover Produto\n");
		printf("[3] Atualizar\n");
		printf("[4] Buscar Produto\n");
		printf("[5] Listar Produto\n");
		printf("[0] Voltar\n");
		printf("======================================\n");
		printf("[x] Digite a opção do Menu >> ");
		fflush(stdin);
		scanf("%d", &opcoes);
		switch(opcoes){
			case 0:{
				menu(db);
				break;
			}
			case 1:{
				system("cls");
				printf("======================================\n");
				printf(" Formulário de Cadastro de Produto\n");
				printf("======================================\n");
				Produto p = registrar_produto();
				rc=0;
				rc = cadastrar_produto(db, &p);
				if(rc == SQLITE_OK){
					system("cls");
					printf("======================================\n");
					printf("Produto Cadastrado com sucesso!\n");
					printf("======================================\n");
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Houve um Error na base de dados!\n");
					printf("======================================\n");
				}
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				char c;
				c = getchar();
				break;
			}
			case 2:{ //delete
				fflush(stdin);
				codigo=0;
				rc=0;
				printf("Digite o código >>");
				scanf("%d",&codigo);
				rc = remover_produto(db, codigo);
				if(rc == SQLITE_OK){
					system("cls");
					printf("======================================\n");
					printf("Produto removido com sucesso!\n");
					printf("======================================\n");
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Houve um Error na base de dados!\n");
					printf("======================================\n");
				}
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				char opc;
				opc = getchar();
				break;
			}
			
			case 3:{
				int opc=0;
				float preco=0.0;
				Produto produto;
				int qtd=0;
				fflush(stdin);
				while(1){
					fflush(stdin);
					system("cls");
					printf("======================================\n");
					printf("Informações a serem atualizadas\n");
					printf("======================================\n");
					printf("[1] - Produto\n");
					printf("[2] - Preço\n");
					printf("[3] - Quantidade\n");
					printf("[4] - Voltar ao Menu.\n");
					scanf("%d", &opc);
					fflush(stdin);
					printf("======================================\n");
					if(opc == 1){
						rc_2=0;
						rc=0;
						codigo=0;
						produto = registrar_produto();
						printf("Codigo:");
						scanf("%d",&codigo);
						fflush(stdin);
						rc=produto_existe(db, codigo);
						if(rc==1){
							rc_2=atualizar_produto_by_codigo(db,codigo,&produto);
							if(rc_2==1){
								printf("======================================\n");
								printf(" PRODUTO ATUALIZADO!\n");
								printf("======================================\n");
							}
							else{
								printf("======================================\n");
								printf(" ERROR AO ATUALIZAR!\n");
								printf("======================================\n");
							}
							break;
						}
						else{
							printf("======================================\n");
							printf(" ERROR AO ATUALIZAR!\n");
							printf(" PRODUTO NÃO EXISTE\n");
							printf("======================================\n");
							break;
						}
					}
					else if(opc == 2){
						codigo=0;
						preco=0.0;
						printf("======================================\n");
						printf(" ATUALIZAR PREÇO DO PRODUTO\n");
						printf("======================================\n");
						printf("Codigo:");
						scanf("%d",&codigo);
						fflush(stdin);
						printf("Preço: ");
						scanf("%f",&preco);
						fflush(stdin);
						rc=0;
						rc_2=0;
						rc=produto_existe(db, codigo);
						if(rc==1){
							rc_2=atualizar_produto_preco_by_codigo(db,codigo,preco);
							if(rc_2 == 1){
								printf("======================================\n");
								printf(" PREÇO ATUALIZADO!\n");
								printf("======================================\n");	
							}
							else{
								printf("======================================\n");
								printf(" ERROR AO ATUALIZAR!\n");
								printf("======================================\n");	
							}
							
							break;
						}
						else{
							printf("======================================\n");
							printf(" ERROR AO ATUALIZAR!\n");
							printf(" PRODUTO NÃO EXISTE\n");
							printf("======================================\n");
							break;
						}
					}
					else if(opc == 3){
						codigo=0;
						preco=0.0;
						fflush(stdin);
						printf("======================================\n");
						printf(" ATUALIZAR QTD NO ESTOQUE.\n");
						printf("======================================\n");
						printf("Codigo:");
						scanf("%d",&codigo);
						fflush(stdin);
						printf("Qtd: ");
						scanf("%d",&qtd);
						fflush(stdin);
						rc=0;
						rc_2=0;
						rc=produto_existe(db, codigo);
						if(rc==1){
							rc_2=atualizar_produto_qtd_by_codigo(db,codigo,qtd);
							if(rc==1){
								printf("======================================\n");
								printf(" Qtd ATUALIZADO!\n");
								printf("======================================\n");
							}
							else{
								printf("======================================\n");
								printf(" Error!\n");
								printf("======================================\n");
							}
							break;
						}
						else{
							printf("======================================\n");
							printf(" ERROR AO ATUALIZAR!\n");
							printf(" PRODUTO NÃO EXISTE\n");
							printf("======================================\n");
							break;
						}
					}
					else if(opc == 4){
						break;
					}
					else{
						fflush(stdin);
						printf("======================================\n");
						printf("Opção Inválida!\n");
						printf("======================================\n");
						char c;
						c = getchar();
						fflush(stdin);
						continue;
					}
					
				}
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				char c;
				c = getchar();
				break;
			}
			
			case 4:{
				fflush(stdin);
				codigo=0;
				rc=0;
				Produto produto;
				system("cls");
				printf("======================================\n");
				printf("Digite o código do produto: ");
				scanf("%d",&codigo);
				fflush(stdin);
				rc=buscar_produto_by_codigo(db, codigo, &produto);
				if(rc==1){
					printf("======================================\n");
					printf("[Produto Encontrado]\n");
					printf("======================================\n");
					printf("Código:%d\n",produto.codigo);
					printf("Nome: %s", produto.nome);
					printf("Preço:%.2f\n", produto.preco);
					printf("Qtd:%d\n", produto.qtd);
					printf("======================================\n");
				}
				else{
					printf("======================================\n");
					printf(" PRODUTO NÃO ENCONTRADO\n");
					printf("======================================\n");
				}
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				char c;
				c = getchar();
				break;
			}
			
			case 5:{ //listar
				system("cls");
				printf("======================================\n");
				printf(" LISTA DE PRODUTOS\n");
				printf("======================================\n");
				listar_produtos(db);
				printf("======================================\n");
				printf(" FINAL DA LISTA\n");
				printf("======================================\n");
				printf(" Tecle [ENTER] para voltar Menu.\n");
				char c;
				c = getchar();
				break;
			}
			default:{
				fflush(stdin);
				system("cls");
				printf("======================================\n");
				printf("Opção Inválida\nTecle [ENTER] para continuar!\n");
				printf("======================================\n");
				char c;
				c = getchar();
			}
		}	
	}
}

void menu_caixa(sqlite3 *db){
	int opcoes=-1;
	int status, qtd_item;
	float desconto, total, preco_total;
	desconto=0.0;
	preco_total=0.0;
	total=0.0;
	status=0;
	qtd_item=0;
	int codigo;
	Node * head=NULL;
	while(1){
		fflush(stdin);
		system("cls");
		printf("======================================\n");
		printf(" CAIXA DE COMPRAS\n");
		printf(" Vendor: %s\n", vendedor);
		printf("======================================\n");
		printf("[1] - Registrar Produto\n");
		printf("[2] - Fechar Compra\n");
		printf("[3] - Visualizar Carrinho de Compra\n");
		printf("[4] - Remover Item do Carinho\n");
		printf("[5] - Atualizar Qtd de Item do Carinho\n");
		printf("[6] - Diminuir Qtd de Item no Carinho\n");
		printf("[7] - Limpar Carinho\n");
		printf("[0] - Voltar ao Menu.\n");
		scanf("%d", &opcoes);
		fflush(stdin);
		switch(opcoes){
			case 0:{
				menu(db);
				break;
			}
			case 1:{ //adicionar produto ao carinho.
				codigo=0;
				system("cls");
				printf("======================================\n");
				printf("Código do Produto: ");
				scanf("%d", &codigo);
				fflush(stdin);
				Produto produto;
				status=verificarProduto(db, codigo, &produto);
				//status=buscar_produto_by_codigo(db, codigo, &produto);
				if(status==1){
					produto.qtd=1;
					addCartInicio(&head, produto);
					printLista(head);
					float total;
					total=calcularPrecoTotal(head);
					printf("Preço Total: %.2f\n", total);
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Produto não encontrado!\n");
					printf("======================================\n");
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c = getchar();
				break;
			}
			case 2:{ //fechar compra
				opcoes=0;
				desconto=0.0;
				total=0.0;
				if(isListaEmpty(head)==true){
					system("cls");
					printf("======================================\n");
					printf("Impossivel, Lista vázia!\n");
					printf("======================================\n");
				}
				else{
					printLista(head);
					fflush(stdin);
					printf("Deseja finalizar a compra?\n");
					printf("[1] Sim ou [0] Não?\n");
					scanf("%d", &opcoes);
					fflush(stdin);
					
					if(opcoes == 1){
						printf("Quantos porcentos de Desconto: ");
						scanf("%f", &desconto);
						fflush(stdin);
						total=calcularPrecoTotal(head);
						preco_total= total-calcularDesconto(total, desconto);
						printf("Preço Total: R$ %.2f\n", preco_total);
						int tam_vetor = qtdItems(head);
						Produto produto[tam_vetor];
						fecharCompra(tam_vetor, head, db, produto);
				  		menu_pagamento_forma(tam_vetor, db, preco_total, vendedor, produto);
					    limparCart(&head);
					}
					else{
						break;
					}
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c = getchar();
				break;
			}
			case 3:{ //Mostrar o carinho de compra.
				fflush(stdin);
				if(isListaEmpty(head)!=true){
					system("cls");
					printLista(head);
					total=0.0;
					total=calcularPrecoTotal(head);
					preco_total= total-calcularDesconto(total, desconto);
					printf("Preço Total: % .2f\n", preco_total);
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Impossivel, Lista vázia!\n");
					printf("======================================\n");
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c = getchar();
				break;
			}
			case 4:{ //remover item do carinho
				fflush(stdin);
				if(isListaEmpty(head)!=true){
					system("cls");
					codigo=0;
					printf("Digite o código do produto do carinho pra remover:");
					scanf("%d", &codigo);
					fflush(stdin);
					removerCart(&head, codigo);	
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Impossivel, Lista vázia!\n");
					printf("======================================\n");
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c=getchar();
				break;
			}
			case 5:{ //atualizar qtd item no carrinho.
				fflush(stdin);
				if(isListaEmpty(head)!=true){
						system("cls");
						codigo=0;
						printf("Códig do Item: ");
						scanf("%d",&codigo);
						fflush(stdin);
						printf("Qtd: ");
						scanf("%d", &qtd_item);
						fflush(stdin);
						Produto produto;
						status=verificarProduto(db, codigo, &produto);
						if(status==1){
							atualizarQtdItem(&head, produto, qtd_item);
							printLista(head);
							float total;
							total=calcularPrecoTotal(head);
							printf("Preço Total: %.2f\n", total);
							printf("Qtd ATUALIZADA\n");
						}
						else{
							system("cls");
							printf("======================================\n");
							printf("Produto não encontrado!\n");
							printf("======================================\n");
						}
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Impossivel, Lista vázia!\n");
					printf("======================================\n");
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c = getchar();
				break;
			}
			case 6:{ //diminuir qtd
				fflush(stdin);
				if(isListaEmpty(head)!=true){
					system("cls");
					codigo=0;
					printf("Códig do Item: ");
					scanf("%d",&codigo);
					fflush(stdin);
					Produto produto;
					status=verificarProduto(db, codigo, &produto);
					if(status==1){
						if(produto.qtd==1){
							limparCart(&head);
						}
						else{
							diminuirQtdItemCart(&head, produto);
							printLista(head);
							float total;
							total=calcularPrecoTotal(head);
							printf("Preço Total: %.2f\n", total);
							printf("Qtd ATUALIZADA\n");
						}
					}
					else{
						system("cls");
						printf("======================================\n");
						printf("Produto não encontrado!\n");
						printf("======================================\n");
					}	
				}
				else{
					system("cls");
					printf("======================================\n");
					printf("Impossivel, Lista vázia!\n");
					printf("======================================\n");
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c = getchar();
				break;
			}
			case 7:{ //Limpar Carinho de Compra
				fflush(stdin);
				system("cls");
				if(isListaEmpty(head)==true){
					printf("O carrinho já está vázio!\n");
				}
				else{
					limparCart(&head);
					printf("Carrinho de Compra vázio!\n");
				}
				char c;
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				c=getchar();
				break;
			}
			default:{
				fflush(stdin);
				system("cls");
				printf("======================================\n");
				printf("Opção Inválida!\n");
				printf("======================================\n");
				printf("Tecle [ENTER] para voltar ao Menu.\n");
				printf("======================================\n");
				char c;
				c = getchar();
			}
		}
	}
}

//menu cliente
void menu_cliente(sqlite3 * db){
	getNone();
}

//construção.
void getNone(){
	printf("Página ainda em construção\n");
	printf("Tecle [ENTER] pra voltar ao Menu.\n");
	char opc;
	opc = getchar();
}
