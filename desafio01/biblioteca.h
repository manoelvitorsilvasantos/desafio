#ifndef SUDOKU_H
#define SUDOKU_H
#define size 9 
	//prototipos das funções e procedimentos.
	int ** criar();
	int verificar(int ** tab, int *row, int* col);
	int verificarBox(int ** tab, int row, int col, int valor);
	int resolverSudoku(int **tab);
	int ** clonarTab(int **tab);
	void usuarioEscolha(int ** tab, int ** ref);
	void imprimir(int** tab);
	
#endif
