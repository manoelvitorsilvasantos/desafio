#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char* qrcode);
void saida(int i, float *s);

int main(int argc, char** argv){
    /*
	char qrcode[32];
    while(1){
        printf("QRCODE >> ");
        scanf("%32s", qrcode);
        
        if(isValid(qrcode)){
            printf("Valid!\n");
            printf("%s\n", qrcode);
        }
        else{
            printf("Invalid!\n");
        }
    }
	*/
	
	float x;
	int i;
	printf("Digite o valor real >> ");
	scanf("%d", &i);
	saida(i, &x);
	printf("%.2f\n", x);
    return 0;
}

void saida(int i, float *s){
	if(i >= 1){
		*s = 10.0f;
	}
}

bool isValid(char *qrcode){
    return strcmp(qrcode, "9f75f950e4865874a67c4ed8e005ab70")==0;
}

