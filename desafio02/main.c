#include "lib/principal.c"
#include "lib/utils.h"

int main() {
	setlocale(LC_ALL, "Portuguese");
	sqlite3* db; 
    int rc;
    rc = sqlite3_open("lib/database.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Não é possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    else{
    	printf("\n");
    	printf("======================================\n");
    	printf("[Database Ok]\n");
    	printf("======================================\n");
	}
	
	while(1){
		system("cls");
		char username[30];
		char password[30];
		fflush(stdin); //limpar buffer do teclado.
		int status = getLogin(username, password);
		fflush(stdin); 
		
		if(status == 1){
			menu(db);
		}
		else{
			system("cls");
			printf("Usuário ou Senha Incorreto!\nTecle [ENTER] para tentar novamente.\n");
			char c;
			c = getchar();
			continue;
		}
	}
	sqlite3_close(db);
    return 0;
}


//logar.
int getLogin(char *user, char *password) {
    int i = 0;
    char c;
	
	printf("======================================\n");
    printf("Digite seu nome de usuário: ");
    scanf("%s", user);
    fflush(stdin);
    printf("Digite sua senha: ");
    while (1) {
        c = getch();  // lê o próximo caractere sem imprimi-lo
        if (c == '\r') {  // se o usuário pressionar Enter
            password[i] = '\0';  // adiciona um terminador de string
            break;  // sai do loop
        } else {
            password[i] = c;
            putchar('*');  // imprime um asterisco no lugar do caractere digitado
            i++;
        }
    }
    
    int status=0;
    FILE *arquivo = fopen("lib/users.bin", "rb");
    if(arquivo==NULL)
    {
    	printf("Erro ao abrir banco de dados.\n");
    	exit(1);
    }
    else{
    	Usuario u;
    	toUpper(user);
    	while(fscanf(arquivo,"%d %s %s %s %d\n",&u.codigo,u.usuario,u.senha,u.email,&u.state)==5){
    		if(strcmp(u.usuario,user)==0 && strcmp(u.senha,password)==0){
    			status+=1;
    			strcpy(vendedor, u.usuario);
    		}
			else{
				continue;
			}	
    	}
    }
    fclose(arquivo);
    return status;
}

void toUpper(char * str){
	int i=0;
	while(str[i]){
		str[i] = tolower(str[i]);
		i++;
	}
}


