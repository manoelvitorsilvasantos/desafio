#ifndef _PIX_H_
#define _PIX_H_
#define MAX_HASH_LEN 64
#define TAM_CNPJ 14
#define PIX_NUBANK "6e3decef5a225dfd1c64954f2bfb77eb"
#define PIX_PICPAY "01d9117d55a6c48a04a1ae71d72fa808"
#define PIX_BRADESCO "43e61f6bbf205f1ddc2faa8803834a99"
#define PIX_SANTADER "bdccdc17e7799dedea4948ee713ad50d"
#define PIX_BB "8c281751b8e053d803767f2f76082081"
#define PIX_ITAU "fc0a2f75f6bdefde9805b0ad08976dc5"
#define PIX_CAIXA "9f75f950e4865874a67c4ed8e005ab70"
#include "libs.h"
#include "banco.h"
#ifdef __cplusplus
extern "C"{
#endif
bool salvar(const char* pix, const char* qrcode, const char* banco_codigo);
void mostrarChaves();
void md5(const char* str, char *result);
void gerar_cnpj(int cnpj[TAM_CNPJ]);
void formatar_cnpj(int *cnpj, char* cnpj_formatado);
void gerar_qrcode(char* chave_pix, char* qrcode);
void gerar_chave_pix(char *nome_banco, char *cod_banco, char* cnpj_usuario, char *chave_pix);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
