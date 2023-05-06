#include "libs.h"
#include "pix.h"

void gerar_chave_pix(char *nome_banco, char *cod_banco, char* cnpj_usuario, char *chave_pix){
	char rand_str[MAX_CHAVE_PIX];
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const int charset_size = strlen(charset);
	srand(time(NULL));
	int i=0;
	for(i=0;i<MAX_CHAVE_PIX;i++){
		rand_str[i] = charset[rand()%charset_size];
	}
	rand_str[MAX_CHAVE_PIX - 1] = '\0';
	snprintf(chave_pix, MAX_CHAVE_PIX, "%s%s%s%s", nome_banco, cod_banco,cnpj_usuario, rand_str);
}

void gerar_qrcode(char* chave_pix, char* qrcode){
	snprintf(qrcode, MAX_CHAVE_PIX + 10, "qrcode-pix:%s", chave_pix);
	
}
