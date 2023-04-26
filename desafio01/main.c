/**
* Programa Desenvolvido no DevCpp++.
* By Manoel Vitor Silva Santos.
* Data: 09/04/2023.
* Desafio 01.
*/

//bibliotecas necessárias.
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.h"

int main(){	
    int** tab = criar();
    int ** userTab = clonarTab(tab);
    int** refTab = clonarTab(tab);
    setlocale(LC_ALL, "Portuguese");
    printf("============================================================================\n");
    printf("          sudoku v.1.0\n");
    printf("============================================================================\n");
    printf("Regras do Jogo:\n\n");
    printf("1. Cada linha deve conter os números de 1 a 9, sem repetições.\n");
    printf("2. Os números de 1 a 9 apenas podem estar presentes uma vez por coluna.\n");
    printf("3. Cada dígito apenas pode estar presente uma vez por grupo.\n");
    printf("4. O valor da soma de cada linha, coluna e grupo é de 45.\n");
    printf("Aperte [q] se você conseguir resolver o jogo.\n");
    imprimir(userTab);
    usuarioEscolha(userTab,refTab);
    //libera memoria.
	free(tab);
    free(userTab);
    free(refTab);
}

int ** criar(){ //criar um vetor dinamicamente.
	//inicializa variaveis para não pegar lixo da memoria.
	int i=0,j=0;
	int ** tab;
	int vet[size][size]={
		9, 8, 7,   4, 0, 3,   0, 2, 6,
        0, 0, 0,   2, 0, 6,   9, 0, 0,
    	0, 0, 5,   0, 0, 0,   0, 0, 1,
        0, 0, 1,   0, 0, 8,   0, 0, 7,
        0, 9, 3,   0, 6, 0,   8, 4, 0,
        8, 0, 0,   3, 0, 7,   6, 0, 0,
        5, 0, 0,   0, 0, 2,   1, 6, 0,
        0, 0, 9,   6, 0, 4,   0, 0, 0,
        4, 7, 0,   5, 0, 0,   0, 9, 3, 
	};
	//Aloca dinamicamente na memoria o vetor.
	tab = (int**)malloc(sizeof(int*)*size);
	//percorre o vetor.
	for(i=0;i<size;i++){
		//aloca um vetor de vetor [matriz].
		tab[i]=(int*)malloc(sizeof(int)*size);
		for(j=0;j<size;j++){
			//copia os valores de um vetor para outro.
			tab[i][j]=vet[i][j];
		}
	}
	return tab; //retorna o vetor criado.
}

void imprimir(int** tab){
    int i=0, j=0,a=0;
    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 1; i < 9; i++, a++){
        for(j = 0; j < 9; j++){
            if (j == 0)
                printf(" %d |", a);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", tab[i][j]);
            if (j == 8)
                printf("|");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");
}

int verificar(int** tab, int* row, int* col){
    int i=0,j=0;
    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (tab[i][j] == 0){
                *row = i;
                *col  = j;
                return 1;
            }
        }
    }
    return 0;
}

int verificarBox(int** tab, int row, int col, int valor){
    int i=0,j=0;
    int box_linha=0, box_coluna=0;
    //verificar linhas
    for(i = 0; i < 9; i++){
        if (tab[i][col] == valor)
            return 0;
    }
    //verificar colunas.
    for(j = 0; j < 9; j++){
        if (tab[row][j] == valor)
            return 0;
    }
    //percorre o quadrado, verificado os valores do quadrado 3x3.
    box_linha = row - row % 3;
    box_coluna = col - col % 3;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(tab[box_linha + i][box_coluna + j] == valor)
                return 0;
        }
    }
    return 1;
}

int resolverSudoku(int** tab){
    int i=0,j=0,valor=0;
    if(!verificar(tab, &i, &j))
    	return 1;
	for(valor=1;valor<10;valor++){
		if(verificarBox(tab, i, j, valor)){
			tab[i][j]=valor;
			if(resolverSudoku(tab))
				return 1;
			else
				tab[i][j]=0;
		}
	}
    return 0;
}

int ** clonarTab(int ** tab){
	int i=0,j=0;
	int ** novoTab;
	novoTab=(int**)malloc(sizeof(int*)*size);
	for(i=0;i<size;i++){
		novoTab[i]=(int*)malloc(sizeof(int)*9);
		for(j=0;j<size;j++){
			novoTab[i][j]=tab[i][j];
		}
	}
	return novoTab;
}


//menu do jogo.
void usuarioEscolha(int** userTab, int** refTab){
    int i=0,j=0;
    int posX=0, posY=0, userVal=0;
    char c;

    while(1){
    if(!verificar(userTab, &i, &j)){
    	printf("Parabéns!!!\n");
    	printf("\nVocê consegui concluir o Jogo!!!.\n");
        return;
    }

    while(1){
    	printf("\nTecle [ENTER] para continuar ou [q] para fechar.\n");
        c = getchar();
        if((c == 'q') || (c == 'Q')){
            getchar();
            resolverSudoku(userTab);
            printf("\nFechando.:\n");
            imprimir(userTab);
            return;
        }
        else if((c != '\n') && (c != 'q'))
            getchar();
        else
            break;
    }

	printf("\nEntre com as coordenadas do Quadrado \nque você gostaria de inserir\n seguindo esse formato. \"X Y\":\n");
    scanf("%d %d",&posX, &posY);
    while(1){
        if ((posX > 9) || (posX < 1) || (posY > 9) || (posY < 1) || (userTab[posY - 1][posX - 1] != 0)){
        	printf("\nVocê não pode inserir esse valor na coordenada.\n Porfavor, tente uma nova coordenada\n");
            scanf("%d %d",&posX, &posY);
        }
        else {
            posX -= 1;
            posY -= 1;
            break;
        }
    }


	printf("Insira um valor de [1-9]\n");
    scanf("%d", &userVal);
    while(1){
        if((userVal > 9) || (userVal < 1)){
            printf("\nInsira um valor válido:\n");
            scanf("%d", &userVal);
        }
        else break;
    }

    if(verificarBox(userTab, posY, posX, userVal))
        userTab[posY][posX] = userVal;
    else
        printf("\nValor proibido para a coordenada X = %d Y = %d\n, Porfavor, Tente Novamente!!!\n",posX + 1, posY + 1);

    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            refTab[i][j] = userTab[i][j];
        }
    }

    if(!resolverSudoku(refTab)){
        printf("\nValor proibido para a coordenada X = %d Y = %d\n, Porfavor, Tente Novamente!!!\n",posX + 1, posY + 1);
        userTab[posY][posX] = 0;
    }
    getchar();
    imprimir(userTab);
    }

    return;
}
