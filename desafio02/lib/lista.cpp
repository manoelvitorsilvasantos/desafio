#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Produto{
	int codigo;
	 char nome[30];
	 float preco;
	 int qtd;	
}Produto;

// Defini��o da estrutura de um n� da lista
typedef struct node {
    Produto  produto;
    struct node* next;
} Node;

// Fun��o para criar um novo n�
Node* newNode(Produto produto) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->produto = produto;
    node->next = NULL;
    return node;
}

// Fun��o para inserir um novo n� no in�cio da lista
void insertAtBeginning(Node** head, Produto produto) {
    Node* node = newNode(produto);
    node->next = *head;
    *head = node;
}

// Fun��o para inserir um novo n� no final da lista
void insertAtEnd(Node** head, Produto produto) {
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
}

// Fun��o para remover o primeiro n� da lista
void removeFirstNode(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* nodeToRemove = *head;
    *head = nodeToRemove->next;
    free(nodeToRemove);
}

// Fun��o para remover o �ltimo n� da lista
void removeLastNode(Node** head) {
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

// Fun��o para imprimir a lista
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        //
        printf("===================================\n");
        printf("Codigo: %d\n", current->produto.codigo);
        printf("Descri��o:%s\n", current->produto.nome);
        printf("Pre�o: %.2f\n", current->produto.preco);
        printf("Qtd: %d\n", current->produto.qtd);
        current = current->next;
    }
    printf("\n");
}

// Fun��o principal para teste
int main() {
	
	setlocale(LC_ALL, "Portuguese");
    Node* head = NULL;
	
	Produto produto;
	produto.codigo = 1;
	strcpy(produto.nome, "manoel");
	produto.preco = 2.50;
	produto.qtd=1;
    // Testando inser��o no in�cio
    insertAtBeginning(&head, produto);


    // Imprimindo a lista atual
    printList(head);
	
	produto.codigo = 1;
	strcpy(produto.nome, "manoel");
	produto.preco = 2.50;
	produto.qtd=1;
    // Testando inser��o no final
    insertAtEnd(&head,produto);
	
    // Imprimindo a lista atual
    printList(head);

    // Testando remo��o do primeiro n�
    removeFirstNode(&head);

    // Imprimindo a lista atual
    printList(head);

    // Testando remo��o do �ltimo n�
    removeLastNode(&head);

    // Imprimindo a lista atual
    printList(head);

    return 0;
}
