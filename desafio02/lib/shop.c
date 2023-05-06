#include "shop.h"
#include "produto.h"
// Função para criar um novo nó

Node* newNode(Produto produto) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->produto = produto;
    node->next = NULL;
    return node;
}

// Função para inserir um novo nó no início da lista
/*
void addCartInicio(Node** head, Produto produto) {
    Node* node = newNode(produto);
    node->next = *head;
    *head = node;
}*/

void diminuirQtdItemCart(Node** head, Produto produto) {
    int codigo = produto.codigo;
    int qtd = produto.preco;
    Node * current = *head;
    
    while(current!=NULL){
		if(current->produto.codigo==codigo){
			if(current->produto.qtd >1){
				current->produto.qtd -= qtd;
			}
			return;
		}
		current = current->next;
	}
	Node* node = newNode(produto);
    node->next = *head;
    *head = node;
}

void atualizarQtdItem(Node** head, Produto produto, int qtd) {
    int codigo = produto.codigo;
    Node * current = *head;
    
    while(current!=NULL){
		if(current->produto.codigo==codigo){
			current->produto.qtd = qtd;
			return;
		}
		current = current->next;
	}
	Node* node = newNode(produto);
    node->next = *head;
    *head = node;
}


void addCartInicio(Node** head, Produto produto) {
    int codigo = produto.codigo;
    int qtd = produto.qtd;
    Node * current = *head;
    
    while(current!=NULL){
		if(current->produto.codigo==codigo){
			current->produto.qtd += qtd;
			return;
		}
		current = current->next;
	}
	Node* node = newNode(produto);
    node->next = *head;
    *head = node;
}

// Função para inserir um novo nó no final da lista
/*
void addCartFinal(Node** head, Produto produto) {
    Node* node = newNode(produto);
    if (*head == NULL) {
        *head = node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}*/
void addCartFinal(Node** head, Produto produto) {
    int codigo = produto.codigo;
    int qtd = produto.qtd;
    Node* current = *head;

    // Procurar pelo produto na lista
    while (current != NULL) {
        if (current->produto.codigo == codigo) {
            // Produto já existe, atualizar quantidade
            current->produto.qtd += qtd;
            return;
        }
        current = current->next;
    }

    // Produto não encontrado, adicionar novo nó no final
    Node* node = newNode(produto);
    if (*head == NULL) {
        *head = node;
        return;
    }
    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}


// Função para remover o primeiro nó da lista
void removerCartInicio(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* nodeToRemove = *head;
    *head = nodeToRemove->next;
    free(nodeToRemove);
}

// Função para remover o último nó da lista
void removeCartFinal(Node** head) {
    if (*head == NULL) {
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

void removerCart(Node** head, int codigo){
	Node* current=*head;
	Node* prev = NULL;
	while(current!=NULL && current->produto.codigo != codigo){
		prev=current;
		current=current->next;
	}
	if(current==NULL){
		printf("Produto com código %d não foi encontrado!\n", codigo);
		return;
	}
	if(prev==NULL){
		*head=current->next;
	}
	else{
		prev->next = current->next;
	}
	free(current);
	printf("Item com código %d foi removido com sucesso\n", codigo);
}

// Função para imprimir a lista
void printLista(Node* head) {
    Node* current = head;
    while (current != NULL) {
        //
        printf("===================================\n");
        printf("Codigo: %d\n", current->produto.codigo);
        printf("Descrição:%s\n", current->produto.nome);
        printf("Preço: %.2f\n", current->produto.preco);
        printf("Qtd: %d\n", current->produto.qtd);
        current = current->next;
    }
    printf("\n");
}
//fechar compra
void fecharCompra(int TAM, Node* head, sqlite3* db, Produto produto[TAM]) {
    Node* current = head;
    int codigo;
    codigo=0;
    int posicao;
    posicao=0;
	while (current != NULL) {
        printf("===================================\n");
        printf("Codigo: %d\n", current->produto.codigo);
        printf("Descrição:%s\n", current->produto.nome);
        printf("Preço: %.2f\n", current->produto.preco);
        printf("Qtd: %d\n", current->produto.qtd);
        codigo=current->produto.codigo;
		if(codigo==current->produto.codigo && current->produto.qtd!=0){
			produto[posicao].codigo = current->produto.codigo;
			strcpy(produto[posicao].nome, current->produto.nome);
			produto[posicao].preco = current->produto.preco;
			produto[posicao].qtd = current->produto.qtd;
			comprarProduto(db, current->produto.codigo, current->produto.qtd);
			current->produto.qtd=0;
			posicao++;
		}
        current = current->next;
    }
    printf("\n");
}

int qtdItems(Node *head){
	Node* current = head;
	int contador=0;
	while(current!=NULL){
		current=current->next;
		contador++;
	}
	return contador;
}

Produto* atribuirProdutos(Node* head, Produto* produtos, int num_produtos) {
    int i = 0;
    Node* current = head;
    while (current != NULL && i < num_produtos) {
        current->produto = produtos[i];
        current = current->next;
        i++;
    }
    return produtos;
}



float calcularDesconto(float valorTotal, float porcentagemDesconto) {
    float valorDesconto = valorTotal * porcentagemDesconto / 100.0;
    return valorDesconto;
}


float calcularPrecoTotal(Node* head){
	float total=0.0;
	Node* current = head;
	while(current!=NULL){
		//total+= current->produto.preco * current->produto.qtd;
		total += current->produto.preco * current->produto.qtd;
		current=current->next; 
	}	
	return total;
}

void limparCart(Node** head){
	Node * current = *head;
	Node * temp;
	while(current!=NULL){
		temp = current;
		current = current->next;
		free(temp);
	}
	*head=NULL;
}

/*int verificarQtdProdutoCodigoX(Node* head, int codigo){
	int qtd=0;
	Node* current=head;
	while(current!=NULL){
		if(current->produto.codigo==codigo){
			qtd += current->produto.qtd;
		}
		current=current->next;
	}
	return qtd;
}*/

int verificarProduto(sqlite3 * db, int codigo, Produto *item){
	sqlite3_stmt *stmt;
    char sql[1000];
    int rc;
    int status=0;
    sprintf(sql, "SELECT * FROM produtos WHERE codigo = '%d'", codigo);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar consulta SQL: %s\n", sqlite3_errmsg(db));
        status=0;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
    	item->codigo = (int)atoi((const char*) sqlite3_column_text(stmt, 0));
    	strcpy(item->nome, ((const char*)sqlite3_column_text(stmt, 1)));
    	item->preco = (float) atof((const char*) sqlite3_column_text(stmt, 2));
    	item->qtd =1;
    	status=1;
    } 
    sqlite3_finalize(stmt);
    return status;
}

bool isListaEmpty(Node *head){
	if(head == NULL){
		return true;
	}
	return false;
}
