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

// Definição da estrutura de um nó da lista
typedef struct node {
    Produto  produto;
    struct node* next;
} Node;

// Função para criar um novo nó
Node* newNode(Produto produto) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->produto = produto;
    node->next = NULL;
    return node;
}

// Função para inserir um novo nó no início da lista
void insertAtBeginning(Node** head, Produto produto) {
    Node* node = newNode(produto);
    node->next = *head;
    *head = node;
}

// Função para inserir um novo nó no final da lista
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

// Função para remover o primeiro nó da lista
void removeFirstNode(Node** head) {
    if (*head == NULL) {
        return;
    }
    Node* nodeToRemove = *head;
    *head = nodeToRemove->next;
    free(nodeToRemove);
}

// Função para remover o último nó da lista
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

// Função para imprimir a lista
void printList(Node* head) {
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

// Função principal para teste
int main() {
	
	setlocale(LC_ALL, "Portuguese");
    Node* head = NULL;
	
	Produto produto;
	produto.codigo = 1;
	strcpy(produto.nome, "manoel");
	produto.preco = 2.50;
	produto.qtd=1;
    // Testando inserção no início
    insertAtBeginning(&head, produto);


    // Imprimindo a lista atual
    printList(head);
	
	produto.codigo = 1;
	strcpy(produto.nome, "manoel");
	produto.preco = 2.50;
	produto.qtd=1;
    // Testando inserção no final
    insertAtEnd(&head,produto);
	
    // Imprimindo a lista atual
    printList(head);

    // Testando remoção do primeiro nó
    removeFirstNode(&head);

    // Imprimindo a lista atual
    printList(head);

    // Testando remoção do último nó
    removeLastNode(&head);

    // Imprimindo a lista atual
    printList(head);

    return 0;
}
