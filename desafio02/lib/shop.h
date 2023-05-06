#ifndef _SHOP_H_
#define _SHOP_H_
#include "libs.h"
#ifdef __cplusplus
extern "C"{
#endif

void fecharCompra(int TAM, Node* head, sqlite3* db, Produto produto[TAM]);
Node* novoNode(Produto produto);
Produto* atribuirProdutos(Node* head, Produto* produtos, int num_produtos);
int qtdItems(Node *head);
void atualizarQtdItem(Node** head, Produto produto, int qtd);
void diminuirQtdItemCart(Node** head, Produto produto);
void addItem(Node** head, Produto produto);
void addCartInicio(Node** head, Produto produto);
void addCartFinal(Node** head, Produto produto);
void removerCartInicio(Node** head);
void removeCartFinal(Node** head);
void removerCart(Node** head, int codigo);
void printLista(Node* head);
void limparCart(Node** head);
float calcularPrecoTotal(Node* head);
float calcularDesconto(float valorTotal, float porcentagemDesconto);
int verificarProduto(sqlite3 * db, int codigo, Produto *item);
int verificarQtdProdutoCodigoX(Node* head, int codigo);
bool isListaEmpty(Node *head);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
