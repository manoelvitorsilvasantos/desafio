#include "libs.h"
#include "pix.h"
#include "banco.h"
#include "utils.c"

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
	snprintf(chave_pix, MAX_CHAVE_PIX, "%s@%s%s%s", nome_banco, cod_banco,cnpj_usuario, rand_str);
}

void gerar_qrcode(char* chave_pix, char* qrcode){
	snprintf(qrcode, MAX_CHAVE_PIX + 10, "%s", chave_pix);
	
}

void mostrarChaves(){
	srand(time(NULL));
	printf("======================================\n");
	printf("|| LISTA DE CHAVES PIX DA EMPRESA\n");
	printf("======================================\n");
	int cnpj[TAM_CNPJ];
    char CNPJ_FORMATADO[19];
    gerar_cnpj(cnpj);
    formatar_cnpj(cnpj, CNPJ_FORMATADO);
    //char result1[2 * MD5_DIGEST_LENGTH + 1];
    char result2[2 * MD5_DIGEST_LENGTH + 1];
	char CHAVE_PIX[MAX_CHAVE_PIX];
    char QRCODE[MAX_CHAVE_PIX + 10];
	bool foi_salvo=false;
	gerar_chave_pix("NUBANK", NUBANK, CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    
    printf(" NUBANK\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    
    foi_salvo = salvar(CHAVE_PIX, result2, NUBANK);
    if(!foi_salvo){
		printf("ERROR\n");
	}
    
    gerar_chave_pix("PICPAY", PICPAY,CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    
    printf(" PICPAY\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    foi_salvo = salvar(CHAVE_PIX, result2, PICPAY);
    if(!foi_salvo){
		printf("ERROR\n");
	}
	
    gerar_chave_pix("BRADESCO", BRADESCO,CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    
    printf(" BRADESCO\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    
    foi_salvo=salvar(CHAVE_PIX, result2, BRADESCO);
    if(!foi_salvo){
		printf("ERROR\n");
	}
    gerar_chave_pix("SANTADER", SANTADER,CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    
    printf(" SANTADER\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    
    foi_salvo=salvar(CHAVE_PIX, result2, SANTADER);
    if(!foi_salvo){
		printf("ERROR\n");
	}
    gerar_chave_pix("BANCO_DO_BRASIL", BANCO_DO_BRASIL,CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    printf("\n");
    printf(" BANCO DO BRASIL\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    
    foi_salvo=salvar(CHAVE_PIX, result2, BANCO_DO_BRASIL);
    if(!foi_salvo){
		printf("ERROR\n");
	}
    gerar_chave_pix("ITAU", ITAU,CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    
    printf(" ITAU\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    
    foi_salvo=salvar(CHAVE_PIX, result2, ITAU);
    if(!foi_salvo){
		printf("ERROR\n");
	}
    gerar_chave_pix("CAIXA", CAIXA,CNPJ_FORMATADO, CHAVE_PIX);
	//md5(CHAVE_PIX, result1);
    gerar_qrcode(CHAVE_PIX, QRCODE);
    md5(QRCODE, result2);
    
    printf(" CAIXA\n");
    printf(" Chave Pix:%s\n", CHAVE_PIX);
    printf(" QRCODE:%s\n", result2);
    printf("\n");
    
    foi_salvo=salvar(CHAVE_PIX, result2, CAIXA);
   	if(!foi_salvo){
		printf("ERROR\n");
	}
		
}

void formatar_cnpj(int *cnpj, char* cnpj_formatado) {
  sprintf(cnpj_formatado, "%02d.%03d.%03d/%04d-%02d",
          cnpj[0]*10+cnpj[1],
          cnpj[2]*100+cnpj[3]*10+cnpj[4],
          cnpj[5]*100+cnpj[6]*10+cnpj[7],
          cnpj[8]*1000+cnpj[9]*100+cnpj[10]*10+cnpj[11],
          cnpj[12]*10+cnpj[13]);
}

void gerar_cnpj(int cnpj[TAM_CNPJ]){
    int i;
	//gera 12 números aleatórios.
    for(i=0;i<12;i++){
        cnpj[i] = rand() % 10;
    }
    //cálculo do primeiro dígito verificador.
    int pesos1[12] = {5,4,3,2,9,8,7,6,5,4,3,2};
    int soma = 0;
    for(i=0;i<12;i++){
        soma += cnpj[i] * pesos1[i];
    }
    int digito1 = (soma % 11) < 2 ? 0 : 11 - (soma % 11);

    //cálculo do segundo dígito verificador.
    int pesos2[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};
    soma = 0;
    for( i=0;i<12;i++){
        soma += cnpj[i] * pesos2[i];
    }
    soma += digito1 * pesos2[12];
    int digito2 = (soma % 11) < 2 ? 0 : 11 - (soma % 11);

    //preenche o vetor de CNPJ com os números gerados e os dígitos verificadores.
    cnpj[12] = digito1;
    cnpj[13] = digito2;
}




void md5(const char* str, char *result){
	MD5_CTX contexto;
	unsigned char digest[MD5_DIGEST_LENGTH];
	char hexdigest[2 * MD5_DIGEST_LENGTH + 1];
	int i;
	MD5_Init(&contexto);
	MD5_Update(&contexto, str, strlen(str));
	MD5_Final(digest, &contexto);
	for(i=0;i<MD5_DIGEST_LENGTH;i++){
		sprintf(hexdigest + 2 * i, "%02x", digest[i]);
	}
	hexdigest[2 * MD5_DIGEST_LENGTH] = '\0';
	strcpy(result, hexdigest);
}


bool salvar(const char* pix, const char* qrcode, const char* banco_codigo){
	
	sqlite3* db; 
    int rc;
    rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Não é possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }

	rc=0;
    sqlite3_stmt * stmt;
    const char * tail;
	char *sql = "UPDATE empresa SET pix = ?, qrcode = ?, banco_codigo = ? WHERE banco_codigo = ?";
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, &tail);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao preparar declaração: %s\n", sqlite3_errmsg(db));
        return false;
    }

    rc = sqlite3_bind_text(stmt, 1, pix, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'pix código': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
    
	rc = sqlite3_bind_text(stmt, 2, qrcode, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'qrcode': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
    
    rc = sqlite3_bind_text(stmt, 3, banco_codigo, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'banco código': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
    
    rc = sqlite3_bind_text(stmt, 4, banco_codigo, -1, SQLITE_TRANSIENT);
    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao definir parâmetro 'banco código': %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }
    
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE){
        fprintf(stderr, "Erro ao executar declaração: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

