#include "libs.h"

int sizeProduto(Produto produto){
	return sizeof(produto)/sizeof(Produto);
}

int sizeItem(Item item){
	return sizeof(item)/sizeof(Item);
}

int sizeCaixa(Caixa caixa){
	return sizeof(caixa)/sizeof(Caixa);
}

int sizeUsuario(Usuario usuario){
	return sizeof(usuario)/sizeof(Usuario);
}

double percDesconto(float preco_desconto, float preco_original){
	return (preco_desconto/preco_original)*100;
}

