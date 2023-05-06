#ifndef _PIX_H_
#define _PIX_H_
#include "libs.h"
#include "banco.h"
#ifdef __cplusplus
extern "C"{
#endif
void gerar_chave_pix(char *nome_banco, char *cod_banco, char* cnpj_usuario, char *chave_pix);
#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif
