#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char* qrcode);

int main(int argc, char** argv){
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

    return 0;
}

bool isValid(char *qrcode){
    return strcmp(qrcode, "9f75f950e4865874a67c4ed8e005ab70")==0;
}

